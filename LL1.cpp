#include "LL1.h"

LL1::LL1(Scanner *s) {
    sc = s;
    Node *node = new Node();
    strcpy(node->id, "###");
    root = new Tree(NULL, NULL, NULL, node);
    Tree::cur = root;
}

bool isDelta(int t) {
    return t <= DEL_SetFunc;
}

int LL1::LL_1() {
    int t;
    TypeLex lex;
    int flag = 1;

    magazin[z++] = TEnd;
    magazin[z] = netermProgram;

    t = sc->scanner(lex);
    getCurrents(t, lex);

    while (flag) {
        if (isTerminal(magazin[z])) {

            // в верхушке магазина терминал

            if (magazin[z] == t) { // верхушка совпадает с отсканированным терминалом
                if (t == TEnd)
                    flag = 0;
                else {
                    t = sc->scanner(lex); // сканируем новый символ
                    getCurrents(t, lex);

                    z--; // стираем верхушку магазина
                }
            } else {
                sc->printError("неверный символ, ожидался '" + codeToString(magazin[z]) + "'", lex);
                return -1;
            }
        } else if (isDelta(magazin[z])) {
            processingDelta(magazin[z]);
            z--;
        } else {
            switch (magazin[z]) {

                case netermProgram :
                    if (t == TShort || t == TInt || t == TLong) {
                        magazin[z++] = netermProgram;
                        magazin[z++] = netermDescription;
                    } else {
                        epsilon();
                    }
                    break;

                case netermDescription:
                    if (t == TShort || t == TInt || t == TLong) {
                        int *lexems = sc->scanNextAndReturn(5);
                        bool isFunc = false;
                        for (int i = 1; i < 5; i++)
                            if (lexems[i] == TLeftRoundSkob && lexems[i - 1] == TIdent) {
                                isFunc = true;
                                break;
                            }
                        if (isFunc) {
                            magazin[z++] = DEL_EndDecl;
                            magazin[z++] = DEL_EndFunc;
                            magazin[z++] = netermSostOper;
                            magazin[z++] = TRightRoundSkob;
                            magazin[z++] = TLeftRoundSkob;
                            magazin[z++] = DEL_SetFunc;
                            magazin[z++] = TIdent;
                            magazin[z++] = netermType;
                        } else
                            magazin[z++] = netermData;
                    } else {
                        epsilon();
                    }
                    break;

                case netermType:
                    magazin[z++] = DEL_StartDecl;
                    if (t == TShort) {
                        // Запоминаем тип
                        currentType = TDataShort;
                        int *lexems = sc->scanNextAndReturn(1);
                        if (lexems[0] == TInt)
                            magazin[z++] = TInt;
                        delete lexems;
                        magazin[z++] = TShort;
                    } else if (t == TLong) {
                        int *lexems = sc->scanNextAndReturn(2);
                        if (lexems[0] == TLong) {
                            currentType = TDataLongLong;
                            if (lexems[1] == TInt)
                                magazin[z++] = TInt;
                            magazin[z++] = TLong;
                        } else {
                            currentType = TDataLong;
                            if (lexems[0] == TInt)
                                magazin[z++] = TInt;
                        }
                        delete lexems;
                        magazin[z++] = TLong;
                    } else if (t == TInt) {
                        currentType = TDataInt;
                        magazin[z++] = TInt;
                    } else
                        sc->printError("Неверный символ", lex);
//                    magazin[z++] = netermType3;
                    break;
                case netermData:
                    if (t == TShort || t == TInt || t == TLong) {
                        magazin[z++] = DEL_EndDecl;
                        magazin[z++] = TTZpt;
                        magazin[z++] = netermList;
                        magazin[z++] = netermType;
                    } else
                        sc->printError("Неверный символ. Ожидался short, int, long", lex);
                    break;
                case netermList:
                    if (t == TIdent) {
                        magazin[z++] = netermList2;
                        magazin[z++] = netermAssign2;
                        magazin[z++] = DEL_SetVar;
                        magazin[z++] = TIdent;
                    } else
                        sc->printError("Неверный символ. Ожидался идентификатор", lex);
                    break;
                case netermList2:
                    if (t == TZpt) {
                        magazin[z++] = netermList;
                        magazin[z++] = TZpt;
                    } else if (t == TTZpt)
                        epsilon();
                    else
                        sc->printError("Неверный символ. Ожидались символы , ;", lex);
                    break;
                case netermAssign:
                    if (t == TSave) {
                        magazin[z++] = DEL_MatchLeft;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TSave;
                    } else
                        sc->printError("Неверный символ. Ожидались символы =", lex);
                    break;
                case netermAssign2:
                    if (t == TSave) {
                        magazin[z++] = netermAssign;
                    } else if (t == TZpt || t == TTZpt)
                        epsilon();
                    else
                        sc->printError("Неверный символ. Ожидались символы = , ;", lex);
                    break;
                case netermSostOper:
                    if (t == TLeftFigSkob) {
                        magazin[z++] = DEL_EndBlock;
                        magazin[z++] = TRightFigSkob;
                        magazin[z++] = netermBlockSostOper;
                        magazin[z++] = DEL_SetBlock;
                        magazin[z++] = TLeftFigSkob;
                    } else
                        sc->printError("Неверный символ. Ожидались символы {", lex);
                    break;
                case netermBlockSostOper:
                    if (t == TShort || t == TInt || t == TLong) {
                        magazin[z++] = netermBlockSostOper;
                        magazin[z++] = netermData;
                    } else if (t == TFor || t == TReturn || t == TIdent || t == TTZpt || t == TLeftFigSkob) {
                        magazin[z++] = netermBlockSostOper;
                        magazin[z++] = netermOper;
                    } else
                        epsilon();
                    //sc->printError("Неверный символ. Ожидались short, int, long, for, return, ;, идентиф.",lex);
                    break;
                case netermOper:
                    if (t == TFor) {
                        magazin[z++] = netermOper;
                        magazin[z++] = TRightRoundSkob;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TTZpt;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TTZpt;
                        // delta matchLeft
                        //magazin[z++] = DEL_MatchLeft;
                        magazin[z++] = netermAssign;
                        // delta find
                        magazin[z++] = DEL_FindVar;
                        magazin[z++] = TIdent;
                        magazin[z++] = TLeftRoundSkob;
                        magazin[z++] = TFor;
                    } else if (t == TReturn) {
                        magazin[z++] = TTZpt;
                        // delta returnCheck
                        magazin[z++] = DEL_ReturnCheck;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TReturn;
                    } else if (t == TIdent) {
                        magazin[z++] = TTZpt;
                        // delta matchLeft
                        //magazin[z++] = DEL_MatchLeft;
                        magazin[z++] = netermAssign;
                        // delta find
                        magazin[z++] = DEL_FindVar;
                        magazin[z++] = TIdent;
                    } else if (t == TLeftFigSkob) {
                        magazin[z++] = netermSostOper;
                    } else if (t == TTZpt)
                        magazin[z++] = TTZpt;
                    else
                        sc->printError("Неверный символ. Ожидался оператор", lex);
                    break;


                case netermExpr1:
                    magazin[z++] = netermExpr11;
                    magazin[z++] = netermExpr2;
                    break;

                case netermExpr11:
                    if (!expression11(t, lex))
                        sc->printError("Неверный символ. Ожидались ==, !=, ),; ", lex);
                    break;
                case netermExpr2:
                    magazin[z++] = netermExpr21;
                    magazin[z++] = netermExpr3;
                    break;

                case netermExpr21:
                    if (!expression21(t, lex))
                        sc->printError("Неверный символ. Ожидались ==, !=, <=,<,>,>=, ),; ", lex);
                    break;
                case netermExpr3:
                    magazin[z++] = netermExpr31;
                    magazin[z++] = netermExpr4;
                    break;
                case netermExpr31:
                    if (!expression31(t, lex))
                        sc->printError("Неверный символ. Ожидались +,-, ==, !=, <=,<,>,>=, ),; ", lex);
                    break;
                case netermExpr4:
                    magazin[z++] = netermExpr41;
                    magazin[z++] = netermExpr5;
                    break;
                case netermExpr41:
                    if (!expression41(t, lex))
                        sc->printError("Неверный символ. Ожидались *,/,% +,-, ==, !=, <=,<,>,>=, ),; ", lex);
                    break;
                case netermExpr5:
                    if (t == TAddSelf) {
                        // delta CheckUnar
                        magazin[z++] = DEL_CheckUnar;
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TAddSelf;
                    } else if (t == TSubSelf) {
                        // delta CheckUnar
                        magazin[z++] = DEL_CheckUnar;
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TSubSelf;
                    } else if (t == TPlus) {
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TPlus;
                    } else if (t == TMinus) {
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TMinus;
                    } else {
                        magazin[z++] = netermExpr51;
                        magazin[z++] = netermExpr6;
                    }
                    wasConst = false;
                    break;
                case netermExpr51:
                    if (!expression51(t, lex))
                        sc->printError("Неверный символ. Ожидались арифметические и операции сравнения ", lex);
                    break;
                case netermExpr6:
                    if (t == TIdent) {
                        magazin[z++] = netermFuncCallOrVar;
                        magazin[z++] = TIdent;
                    } else if (t == TConst16) {
                        // delta PushType && ConstType
                        magazin[z++] = DEL_ConstType;
                        magazin[z++] = TConst16;
                    } else if (t == TConst10) {
                        // delta PushType && ConstType
                        magazin[z++] = DEL_ConstType;
                        magazin[z++] = TConst10;
                    } else if (t == TLeftRoundSkob) {
                        magazin[z++] = TRightRoundSkob;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TLeftRoundSkob;
                    } else
                        sc->printError("Неверный символ. Ожидались идентификатор, константа, (", lex);
                    break;
                case netermFuncCallOrVar:
                    if (t == TLeftRoundSkob) {
                        // delta PushType && CallFunc
                        magazin[z++] = DEL_CallFunc;
                        magazin[z++] = TRightRoundSkob;
                        magazin[z++] = TLeftRoundSkob;
                    } else {
                        magazin[z++] = DEL_FindVar;
                        epsilon();
                    }
                    break;
            }
            z--;
        }
    }
    printf("// !----- Вывод дерева ----- //\n");
    root->printTree();
    printf("// !----- Конец вывода дерева ----- //\n");
    return 123;
}

void LL1::processingDelta(int delta) {

    switch (delta) {

        // --------------------------------------- Семантика ---------------------------------------

        case DEL_SetVar: {
            root->semAddNode(currentIdent, TNodeVar, currentType, sc);
            types[typz++] = currentType;
            break;
        }

        case DEL_SetFunc: {
            treePointers[tpz++] = root->semAddNode(currentIdent, TNodeFunction, currentType, sc);
            root->setCur(root->getCur()->getRight());
            break;
        }

        case DEL_EndFunc: {
            root->setCur(treePointers[--tpz]);
            break;
        }

        case DEL_FindVar: {
            Tree *var = root->semGetVar(currentIdent, sc);
            if (var != nullptr)
                types[typz++] = var->getNode()->typeData;
            break;
        }

        case DEL_SetBlock: {
            treePointers[tpz++] = root->getCur();
            root->semAddBlock();
            break;
        }


        case DEL_EndBlock: {
            root->setCur(treePointers[--tpz]);
            break;
        }


        case DEL_StartDecl: {
            // установить флаг описания данных
            flagData = true;
            break;
        }

        case DEL_EndDecl: {
            // сбросить флаг описания данных
            flagData = false;
            break;
        }

        case DEL_MatchLeft: {
            int second = subTypesStack();
            int first = subTypesStack();
            if (second > first) {
                sc->printWarningTypes(first, second, WSmallType);
            }
            break;
        }

        case DEL_MatchCompare: {
            int second = subTypesStack();
            int first = subTypesStack();
            types[typz++] = TDataInt;
            break;
        }

        case DEL_Match: {
            int second = subTypesStack();
            int first = subTypesStack();
            types[typz++] = first > second ? first : second;
            break;
        }

        case DEL_CheckUnar: {
            if (wasConst) {
                sc->printError("Попытка применить операторы ++ или -- к константе", false);
            }
            break;
        }

        case DEL_ReturnCheck: {
            Node *cur;
            int i = tpz - 1;
            do {
                cur = treePointers[i--]->getNode();
            } while (cur->typeNode != TNodeFunction && i >= 0);
            if (cur->typeNode != TNodeFunction)
                sc->printError("Не найдено функции в DEL_ReturnCheck");
            int func, expression;
            func = cur->typeData;
            expression = subTypesStack();
            if (expression > func) {
                sc->printWarningTypes(expression, func, WDifferentTypesFunc);
            }
            break;
        }

        case DEL_CallFunc: {
            Tree *func = root->semGetFunc(currentIdent, sc);
            if (func != nullptr)
                types[typz++] = func->getNode()->typeData;
            break;
        }

        case DEL_ConstType: {
            if (currentTypeConst != TConst10 && currentTypeConst != TConst16)
                sc->printError("Ошибка в DEL_ConstType, curTypeLex - не константа ",
                               std::to_string(currentTypeConst).c_str(), false);
            long long constanta = (currentTypeConst == TConst10) ? strtoull(currentConst, nullptr, 10) : strtoull(
                    currentConst, nullptr, 16);
            types[typz++] = sc->getTypeConst(constanta, typeConst);
            break;
        }
    }
}

int LL1::subTypesStack() {
    if (typz == 0)
        sc->printError("Недостаточно типов в магазине");
    return types[--typz];
}

bool LL1::expression11(int t, TypeLex lex, int add) {
    if (t == TEQ) {
        magazin[z++] = netermExpr11 + add;
        // delta match
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr2 + add;
        magazin[z++] = TEQ;
    } else if (t == TNEQ) {
        magazin[z++] = netermExpr11 + add;
        // delta match
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr2 + add;
        magazin[z++] = TNEQ;
    } else if (t == TRightRoundSkob || t == TTZpt || t == TZpt)
        epsilon();
    else {
        return false;
    }
    return true;
}

bool LL1::expression21(int t, TypeLex lex, int add) {
    if (t == TGE) {
        magazin[z++] = netermExpr21 + add;
        // delta match
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr3;
        magazin[z++] = TGE;
    } else if (t == TGT) {
        magazin[z++] = netermExpr21 + add;
        // delta match
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr3 + add;
        magazin[z++] = TGT;
    } else if (t == TLE) {
        magazin[z++] = netermExpr21 + add;
        // delta match
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr3 + add;
        magazin[z++] = TLE;
    } else if (t == TLT) {
        magazin[z++] = netermExpr21 + add;
        // delta match
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr3 + add;
        magazin[z++] = TLT;
    } else if (t == TRightRoundSkob || t == TTZpt || t == TZpt)
        epsilon();
    else
        return expression11(t, lex, add + 2);
    return true;
}

bool LL1::expression31(int t, TypeLex lex, int add) {
    if (t == TPlus) {
        magazin[z++] = netermExpr31 + add;
        // delta match
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr4 + add;
        magazin[z++] = TPlus;
    } else if (t == TMinus) {
        magazin[z++] = netermExpr31 + add;
        // delta match
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr4 + add;
        magazin[z++] = TMinus;
    } else if (t == TRightRoundSkob || t == TTZpt || t == TZpt)
        epsilon();
    else
        return expression21(t, lex, add + 2);
    return true;
}

bool LL1::expression41(int t, TypeLex lex, int add) {
    if (t == TMul) {
        magazin[z++] = netermExpr41 + add;
        // delta match
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TMul;
    } else if (t == TDiv) {
        magazin[z++] = netermExpr41 + add;
        // delta match
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TDiv;
    } else if (t == TMod) {
        magazin[z++] = netermExpr41 + add;
        // delta match
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TMod;
    } else if (t == TRightRoundSkob || t == TTZpt || t == TZpt)
        epsilon();
    else
        return expression31(t, lex, add + 2);
    return true;
}

void LL1::epsilon() {
    //z--;
}

bool LL1::expression51(int t, TypeLex lex) {
    if (t == TAddSelf) {
        // delta checkUn
        magazin[z++] = DEL_CheckUnar;
        magazin[z++] = TAddSelf;
    } else if (t == TSubSelf) {
        // delta match
        magazin[z++] = DEL_CheckUnar;
        magazin[z++] = TSubSelf;
    } else if (t == TRightRoundSkob || t == TTZpt || t == TZpt)
        epsilon();
    else {
        return expression41(t, lex, 2);;
    }
    return true;
}


// обновляем текущий тип, идентификатор и константу, если надо
void LL1::getCurrents(int t, TypeLex lex) {

    if (t == TConst10 || t == TConst16) {
        strcpy(currentConst, lex);
        currentTypeConst = t;
    }
    if (t == TIdent) {
        strcpy(currentIdent, lex);
    }

}

bool LL1::isTerminal(int t) {
    return t < netermProgram && t >= 0;
}

string LL1::codeToString(int code) {
    string str;

    switch (code) {
        case netermProgram:
            str = "нетерминал программа";
            break;
        case netermDescription:
            str = "нетерминал Описание";
            break;
        case netermData:
            str = "нетерминал данные";
            break;
        case netermType:
            str = "нетерминал тип";
            break;
        case netermType2:
            str = "нетерминал тип";
            break;
        case netermType3:
            str = "нетерминал тип";
            break;
        case netermList:
            str = "нетерминал список";
            break;
        case netermList2:
            str = "нетерминал список2";
            break;
        case netermAssign:
            str = "нетерминал присваивание";
            break;
        case netermAssign2:
            str = "нетерминал присваивание2";
            break;
        case netermSostOper:
            str = "нетерминал составной оператор";
            break;
        case netermBlockSostOper:
            str = "нетерминал блок составного оператора";
            break;
        case netermOper:
            str = "нетерминал оператор";
            break;

        case netermExpr1:
            str = "нетерминал выражение1";
            break;
        case netermExpr11:
            str = "нетерминал выражение1.1";
            break;
        case netermExpr2:
            str = "нетерминал выражение2";
            break;
        case netermExpr21:
            str = "нетерминал выражение2.1";
            break;
        case netermExpr3:
            str = "нетерминал выражение3";
            break;
        case netermExpr31:
            str = "нетерминал выражение3.1";
            break;
        case netermExpr4:
            str = "нетерминал выражение4";
            break;
        case netermExpr41:
            str = "нетерминал выражение4.1";
            break;
        case netermExpr5:
            str = "нетерминал выражение5";
            break;
        case netermExpr51:
            str = "нетерминал выражение5.1";
            break;
        case netermExpr6:
            str = "нетерминал выражение6";
            break;

        case netermFuncCallOrVar:
            str = "нетерминмал вызов ф-ии или переменная";
            break;

        case TIdent:
            str = "идентификатор";
            break;
        case TConst10:
            str = "константа 10сс";
            break;
        case TConst16:
            str = "константа 16сс";
            break;

        case TReturn:
            str = "return";
            break;
        case TFor:
            str = "for";
            break;
        case TInt:
            str = "int";
            break;
        case TShort:
            str = "short";
            break;
        case TLong:
            str = "long";
            break;
        case TPlus:
            str = "+";
            break;
        case TMinus:
            str = "-";
            break;
        case TMul:
            str = "*";
            break;
        case TDiv:
            str = "/";
            break;
        case TMod:
            str = "%";
            break;
        case TSave:
            str = "=";
            break;
        case TAddSelf:
            str = "++";
            break;
        case TSubSelf:
            str = "--";
            break;
        case TGT:
            str = ">";
            break;
        case TLT:
            str = "<";
            break;
        case TGE:
            str = ">=";
            break;
        case TLE:
            str = "<=";
            break;
        case TEQ:
            str = "==";
            break;
        case TNEQ:
            str = "!=";
            break;

        case TLeftRoundSkob:
            str = "(";
            break;
        case TRightRoundSkob:
            str = ")";
            break;
        case TLeftFigSkob:
            str = "{";
            break;
        case TRightFigSkob:
            str = "}";
            break;
        case TTZpt:
            str = ";";
            break;
        case TZpt:
            str = ",";
            break;

        case TErr:
            str = "TError";
            break;
        case TEnd:
            str = "TEnd";
            break;

        default:
            cerr << " Неизвестный код в LL1::codeToString: " << code << endl;
            str = "TError";
            break;
    }

    return str;
}
