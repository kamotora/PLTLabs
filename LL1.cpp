#include "LL1.h"
#include "Node.h"
#include "exception/EmptyCollectionError.h"

LL1::LL1(Scanner *s) {
    sc = s;
    Node *node = new Node();
    strcpy(node->id, "###");
    root = new Tree(NULL, NULL, NULL, node);
    Tree::cur = root;
}

bool LL1::isDelta(int t) {
    return t <= DEL_SetFunc && !isGenFunc(t);
}

bool LL1::isGenFunc(int t) {
    return t <= GEN_PUSH;
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
        } else if (isGenFunc(magazin[z])) {
            processingGenFunc(magazin[z]);
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
                            magazin[z++] = GEN_ENDP;
                            magazin[z++] = DEL_EndDecl;
                            magazin[z++] = DEL_EndFunc;
                            magazin[z++] = netermSostOper;
                            magazin[z++] = TRightRoundSkob;
                            magazin[z++] = TLeftRoundSkob;
                            magazin[z++] = GEN_PROC;
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
                        currentTypeData = TDataShort;
                        int *lexems = sc->scanNextAndReturn(1);
                        if (lexems[0] == TInt)
                            magazin[z++] = TInt;
                        delete lexems;
                        magazin[z++] = TShort;
                    } else if (t == TLong) {
                        int *lexems = sc->scanNextAndReturn(2);
                        if (lexems[0] == TLong) {
                            currentTypeData = TDataLongLong;
                            if (lexems[1] == TInt)
                                magazin[z++] = TInt;
                            magazin[z++] = TLong;
                        } else {
                            currentTypeData = TDataLong;
                            if (lexems[0] == TInt)
                                magazin[z++] = TInt;
                        }
                        delete lexems;
                        magazin[z++] = TLong;
                    } else if (t == TInt) {
                        currentTypeData = TDataInt;
                        magazin[z++] = TInt;
                    } else
                        sc->printError("Неверный символ", lex);
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
                        magazin[z++] = GEN_PUSH;
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
                        magazin[z++] = GEN_ASSIGNMENT;
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
                        magazin[z++] = GEN_FORM_IF;
                        magazin[z++] = GEN_SET_ADDR_NOP; // end
                        magazin[z++] = GEN_GOTO_STEP; // goto step
                        magazin[z++] = netermOper;
                        magazin[z++] = GEN_SET_LOOP_ADDR; // body
                        magazin[z++] = TRightRoundSkob;
                        magazin[z++] = GEN_GOTO_IF;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = GEN_SET_LOOP_ADDR; // step
                        magazin[z++] = TTZpt;
                        magazin[z++] = GEN_IF;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = GEN_SET_LOOP_ADDR; // conditional
                        magazin[z++] = TTZpt;
                        magazin[z++] = netermAssign;
                        magazin[z++] = GEN_PUSH;
                        // delta find
                        magazin[z++] = DEL_FindVar;
                        magazin[z++] = TIdent;
                        magazin[z++] = TLeftRoundSkob;
                        magazin[z++] = GEN_FOR;
                        magazin[z++] = TFor;
                    } else if (t == TReturn) {
                        magazin[z++] = TTZpt;
                        // delta returnCheck
                        magazin[z++] = DEL_ReturnCheck;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TReturn;
                    } else if (t == TIdent) {
                        magazin[z++] = TTZpt;
                        magazin[z++] = netermAssign;
                        magazin[z++] = GEN_PUSH;
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
                        magazin[z++] = GEN_PLUS;
                        magazin[z++] = GEN_PUSH_ONE;
                        // delta CheckUnar
                        magazin[z++] = DEL_CheckUnar;
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TAddSelf;
                    } else if (t == TSubSelf) {
                        magazin[z++] = GEN_MINUS;
                        magazin[z++] = GEN_PUSH_ONE;
                        // delta CheckUnar
                        magazin[z++] = DEL_CheckUnar;
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TSubSelf;
                    } else if (t == TPlus) {
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TPlus;
                    } else if (t == TMinus) {
                        // -5 = -1 * 5
                        magazin[z++] = GEN_MUL;
                        magazin[z++] = netermExpr6;
                        magazin[z++] = GEN_PUSH_MINUS_ONE;
                        magazin[z++] = TMinus;
                    } else {
                        magazin[z++] = netermExpr51;
                        magazin[z++] = netermExpr6;
                    }
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
                        magazin[z++] = GEN_PUSH;
                        // delta PushType && ConstType
                        magazin[z++] = DEL_ConstType;
                        magazin[z++] = TConst16;
                    } else if (t == TConst10) {
                        magazin[z++] = GEN_PUSH;
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
//                        magazin[z++] = GEN_PUSH;
                        // delta PushType && CallFunc
                        magazin[z++] = GEN_CALL;
                        magazin[z++] = DEL_CallFunc;
                        magazin[z++] = TRightRoundSkob;
                        magazin[z++] = TLeftRoundSkob;
                    } else {
                        magazin[z++] = GEN_PUSH;
                        magazin[z++] = DEL_FindVar;
                        epsilon();
                    }
                    break;
            }
            z--;
        }
    }
    cout << "// !----- Вывод дерева ----- //\n";
    root->printTree();
    cout << "// !----- Конец вывода дерева ----- //\n";
    return 123;
}

void LL1::processingDelta(int delta) {

    switch (delta) {

        // --------------------------------------- Семантика ---------------------------------------

        case DEL_SetVar: {
            currentTypeNode = TNodeVar;
            root->semAddNode(currentIdentOrConst, TNodeVar, currentTypeData, sc);
            pushType(currentTypeData, TNodeVar);
            break;
        }

        case DEL_SetFunc: {
            treePointers[tpz++] = root->semAddNode(currentIdentOrConst, TNodeFunction, currentTypeData, sc);
            root->setCur(root->getCur()->getRight());
            currentTypeNode = TNodeFunction;
            break;
        }

        case DEL_EndFunc: {
            root->setCur(treePointers[--tpz]);
            break;
        }

        case DEL_FindVar: {
            Tree *var = root->semGetVar(currentIdentOrConst, sc);
//            operands.push_back(new Operand(var->getNode()));
            currentTypeData = var->getNode()->typeData;
            currentTypeNode = TNodeVar;
            pushType(var);
            break;
        }

        case DEL_SetBlock: {
            treePointers[tpz++] = root->semAddBlock();
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
            //todo вынести общий код, а то не красиво как-то
            int typeDataOperand1 = getTypeDataOperand(operands[operands.size() - 2]);
            int typeDataOperand2 = getTypeDataOperand(operands[operands.size() - 1]);
            if (typeDataOperand1 != typeDataOperand2) {
                if (typeDataOperand1 > typeDataOperand2) {
                    sc->printWarningTypes(typeDataOperand2, typeDataOperand1, WSmallType);
                }
                triads.push_back(getCastTypeTriad(typeDataOperand2, typeDataOperand1, operands[operands.size() - 1]));
                operands.pop_back();
                operands.push_back(new Operand(getLastTriadAddr()));
            }
            break;
        }

        case DEL_MatchCompare: {
            int second = subTypesStack();
            int first = subTypesStack();
            pushType(TDataInt, TNodeConst);
            break;
        }

        case DEL_Match: {
            int typeDataOperand1 = getTypeDataOperand(operands[operands.size() - 2]);
            int typeDataOperand2 = getTypeDataOperand(operands[operands.size() - 1]);
            if (typeDataOperand1 > typeDataOperand2) {
                triads.push_back(getCastTypeTriad(typeDataOperand2, typeDataOperand1, operands[operands.size() - 1]));
                operands.pop_back();
                operands.push_back(new Operand(getLastTriadAddr()));
            } else if (typeDataOperand1 < typeDataOperand2) {
                triads.push_back(getCastTypeTriad(typeDataOperand1, typeDataOperand2, operands[operands.size() - 2]));
                operands.pop_back();
                operands.push_back(new Operand(getLastTriadAddr()));
            }
            int second = subTypesStack();
            int first = subTypesStack();
            pushType(first > second ? first : second, TNodeConst);
            break;
        }

        case DEL_CheckUnar: {
            if (types.empty() || types.back().second != TNodeVar)
                sc->printError("Попытка применить операторы ++ или -- не к переменной", false);
            break;
        }

        case DEL_ReturnCheck: {
            //todo вынести общий код, а то не красиво как-то


            auto funcTriad = triads[funcTriads.back()];
            if (funcTriad->getOperand1()->type != NODE ||
                funcTriad->getOperand1()->value.node->typeNode != TNodeFunction)
                sc->printError("Не найдено функции в DEL_ReturnCheck");
            Node *cur = funcTriad->getOperand1()->value.node;
//            int i = tpz - 1;
//            do {
//                cur = treePointers[i--]->getNode();
//            } while (cur->typeNode != TNodeFunction && i >= 0);
            // Проверка возвращаемого типа и типа выражения в return;
            auto returnExpressionOperand = operands[operands.size() - 1];
            int funcTypeData, expressionTypeData;
            funcTypeData = cur->typeData;
            expressionTypeData = getTypeDataOperand(returnExpressionOperand);
            if (expressionTypeData != funcTypeData) {
                triads.push_back(getCastTypeTriad(expressionTypeData, funcTypeData, returnExpressionOperand));
                if (expressionTypeData > funcTypeData)
                    sc->printWarningTypes(expressionTypeData, funcTypeData, WDifferentTypesFunc);
            }

            triads.push_back(new Triad(TRI_MOV, getOperand(), new Operand("eax")));
            operands.push_back(new Operand(getLastTriadAddr()));
            triads.push_back(new Triad(TRI_RET));
            break;
        }

        case DEL_CallFunc: {
            Tree *func = root->semGetFunc(currentIdentOrConst, sc);
            operands.push_back(new Operand(func->getNode()));
            pushType(func);
            break;
        }

        case DEL_ConstType: {
            long long constanta = (currentTypeData == TConst10) ? strtoull(currentIdentOrConst, nullptr, 10) : strtoull(
                    currentIdentOrConst, nullptr, 16);
            auto typeConst = sc->getTypeConst(constanta);
            pushType(typeConst, TNodeConst);
            currentTypeNode = TNodeConst;
            currentTypeData = typeConst;
            break;
        }
    }
}

void LL1::pushType(int dataType, int nodeType) { types.push_back(make_pair(dataType, nodeType)); }

int LL1::subTypesStack() {
    if (types.empty())
        sc->printError("Недостаточно типов в магазине. Переменные в выражении не определены ранее");
    int res = types.back().first;
    types.pop_back();
    return res;
}

void LL1::pushType(Tree *pTree) {
    if (pTree == nullptr)
        return;
    pushType(pTree->getNode()->typeData, pTree->getNode()->typeNode);
}

void LL1::processingGenFunc(int t) {
    switch (t) {
        case GEN_PUSH:
            // todo проверить в дебаге
            operands.push_back(new Operand(new Node(currentTypeNode, currentIdentOrConst, currentTypeData)));
            break;
        case GEN_PUSH_ONE:
            operands.push_back(new Operand(new Node(TNodeConst, "1", TDataShort)));
            break;
        case GEN_PUSH_MINUS_ONE:
            operands.push_back(new Operand(new Node(TNodeConst, "-1", TDataShort)));
            break;
        case GEN_PUSH_ZERO:
            operands.push_back(new Operand(new Node(TNodeConst, "0", TDataShort)));
            break;
        case GEN_ASSIGNMENT:
            generateArithmeticTriad(TRI_ASSIGNMENT);
            break;
        case GEN_EQ:
            generateArithmeticTriad(TRI_EQ);
            break;
        case GEN_NEQ :
            generateArithmeticTriad(TRI_NEQ);
            break;
        case GEN_GT:
            generateArithmeticTriad(TRI_GT);
            break;
        case GEN_GE :
            generateArithmeticTriad(TRI_GE);
            break;
        case GEN_LT:
            generateArithmeticTriad(TRI_LT);
            break;
        case GEN_LE:
            generateArithmeticTriad(TRI_LE);
            break;
        case GEN_FORM_IF: {
            auto loopTriad = getTopValue(loopTriads, "loopTriads");
            // выход из цикла
            Operand *operand2 = new Operand(getTopValue(loopTriad.second, "loopReturnAddresses"));
            triads[loopTriad.first]->setOperand2(operand2);
            // переход к телу цикла
            Operand *operand1 = new Operand(getTopValue(loopTriad.second, "loopReturnAddresses"));
            triads[loopTriad.first]->setOperand1(operand1);
            break;
        }
        case GEN_GOTO_IF: {
            auto returnAddresses = loopTriads.back().second;
            auto condition = returnAddresses[returnAddresses.size() - 2];
            triads.push_back(new Triad(TRI_JMP, new Operand(condition), nullptr));
            break;
        }
        case GEN_GOTO_STEP: {
            auto returnAddresses = loopTriads.back().second;
            auto step = returnAddresses[returnAddresses.size() - 2];
            triads.push_back(new Triad(TRI_JMP, new Operand(step), nullptr));
            break;
        }
        case GEN_SET_LOOP_ADDR: {
            triads.push_back(new Triad(TRI_UNIQUE_LABEL));
            loopTriads.back().second.push_back(getLastTriadAddr());
//            returnAddress.push_back(getLastTriadAddr());
            break;
        }
        case GEN_SET_ADDR_NOP: {
            triads.push_back(new Triad(TRI_NOP));
            loopTriads.back().second.push_back(getLastTriadAddr());
            break;
        }
        case GEN_FOR: {
            loopTriads.push_back(make_pair(0, vector<int>()));
            break;
        }
        case GEN_IF: {
            // goto body (true) or end (false), адреса заполним позже
            triads.push_back(new Triad(TRI_IF, nullptr, nullptr));
            loopTriads.back().first = getLastTriadAddr();
            break;
        }
        case GEN_CMP: {
            generateArithmeticTriad(TRI_CMP);
            break;
        }
        case GEN_MUL: {
            generateArithmeticTriad(TRI_MUL);
            break;
        }

        case GEN_DIV: {
            generateArithmeticTriad(TRI_DIV);
            break;
        }

        case GEN_MOD: {
            generateArithmeticTriad(TRI_MOD);
            break;
        }

        case GEN_PLUS: {
            generateArithmeticTriad(TRI_PLUS);
            break;
        }

        case GEN_MINUS: {
            generateArithmeticTriad(TRI_MINUS);
            break;
        }

        case GEN_CALL: {
            Operand *operand = getOperand();
            triads.push_back(new Triad(TRI_CALL, operand, nullptr));
            operands.push_back(new Operand(getLastTriadAddr()));
            break;
        }
        case GEN_PUSH_PROLOG: {
            operands.push_back(new Operand(new Node(prolog)));
            break;
        }

        case GEN_PUSH_EPILOG: {
            operands.push_back(new Operand(new Node(epilog)));
            break;
        }
        case GEN_PROC: {
            triads.push_back(new Triad(TRI_PROC, new Operand(treePointers[tpz - 1]->getNode()), nullptr));
            funcTriads.push_back(getLastTriadAddr());
            break;
        }
        case GEN_ENDP: {
            auto func = getTopValue(funcTriads, "funcTriads");
            triads.push_back(new Triad(TRI_ENDP, new Operand(triads[func]->getOperand1()->value.node), nullptr));
            break;
        }
        default:
            throw InvalidGenFuncError(t);
    }
}

bool LL1::expression11(int t, TypeLex lex, int add) {
    if (t == TEQ) {
        magazin[z++] = netermExpr11 + add;
        // delta match
        magazin[z++] = GEN_EQ;
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr2 + add;
        magazin[z++] = TEQ;
    } else if (t == TNEQ) {
        magazin[z++] = netermExpr11 + add;
        // delta match
        magazin[z++] = GEN_NEQ;
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
        magazin[z++] = GEN_GE;
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr3;
        magazin[z++] = TGE;
    } else if (t == TGT) {
        magazin[z++] = netermExpr21 + add;
        // delta match
        magazin[z++] = GEN_GT;
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr3 + add;
        magazin[z++] = TGT;
    } else if (t == TLE) {
        magazin[z++] = netermExpr21 + add;
        // delta match
        magazin[z++] = GEN_LE;
        magazin[z++] = DEL_MatchCompare;
        magazin[z++] = netermExpr3 + add;
        magazin[z++] = TLE;
    } else if (t == TLT) {
        magazin[z++] = netermExpr21 + add;
        // delta match
        magazin[z++] = GEN_LT;
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
        magazin[z++] = GEN_PLUS;
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr4 + add;
        magazin[z++] = TPlus;
    } else if (t == TMinus) {
        magazin[z++] = netermExpr31 + add;
        // delta match
        magazin[z++] = GEN_MINUS;
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
        magazin[z++] = GEN_MUL;
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TMul;
    } else if (t == TDiv) {
        magazin[z++] = netermExpr41 + add;
        // delta match
        magazin[z++] = GEN_DIV;
        magazin[z++] = DEL_Match;
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TDiv;
    } else if (t == TMod) {
        magazin[z++] = netermExpr41 + add;
        // delta match
        magazin[z++] = GEN_MOD;
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
    //z--; todo удалить
}

bool LL1::expression51(int t, TypeLex lex) {
    if (t == TAddSelf) {
        // delta checkUn
        magazin[z++] = GEN_PLUS;
        magazin[z++] = GEN_PUSH_ONE;
        magazin[z++] = DEL_CheckUnar;
        magazin[z++] = TAddSelf;
    } else if (t == TSubSelf) {
        // delta match
        magazin[z++] = GEN_MINUS;
        magazin[z++] = GEN_PUSH_ONE;
        magazin[z++] = DEL_CheckUnar;
        magazin[z++] = TSubSelf;
    } else if (t == TRightRoundSkob || t == TTZpt || t == TZpt)
        epsilon();
    else {
        return expression41(t, lex, 2);;
    }
    return true;
}

void LL1::generateArithmeticTriad(int operation) {
    Operand *operand2 = getOperand();
    Operand *operand1 = getOperand();
    triads.push_back(new Triad(operation, operand1, operand2));
    operands.push_back(new Operand(getLastTriadAddr()));
}

Operand *LL1::getOperand() {
    return getTopValue(operands, "operands");
}

int LL1::getTypeDataOperand(Operand *operand) {
    if (operand == nullptr || operand->type == EMPTY)
        return TDataUndefined;
    if (operand->type == NODE)
        return operand->value.node->typeData;
    return getTypeDataTriad(triads[operand->value.address]);
}

template<typename T>
T LL1::getTopValue(vector<T> &st, const string &name) {
    if (st.empty())
        throw EmptyCollectionError("operands");
    auto res = st.back();
    st.pop_back();
    return res;
}

// обновляем текущий тип, идентификатор и константу, если надо
void LL1::getCurrents(int t, TypeLex lex) {

    if (t == TConst10 || t == TConst16 || t == TIdent) {
        strcpy(currentIdentOrConst, lex);
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

void LL1::outTriads() {
    cout << "Триады: " << endl;
    for (int i = 0; i < triads.size(); i++) {
        cout << i << ") ";
        outOneTriad(triads[i]);
        cout << endl;
    }
}

void LL1::outOneTriad(Triad *triad) {
    cout << codeOperationToString(triad->getOperation()) << " ";
    outOneOperand(triad->getOperand1());
    cout << " ";
    outOneOperand(triad->getOperand2());
}

string LL1::codeOperationToString(int code) {
    string str;

    switch (code) {
        case TRI_MUL:
            str = "*";
            break;
        case TRI_DIV:
            str = "/";
            break;
        case TRI_MOD:
            str = "%";
            break;
        case TRI_PLUS:
            str = "+";
            break;
        case TRI_MINUS:
            str = "-";
            break;
        case TRI_ASSIGNMENT:
            str = "=";
            break;
        case TRI_GT:
            str = ">";
            break;
        case TRI_LT:
            str = "<";
            break;
        case TRI_GE:
            str = ">=";
            break;
        case TRI_LE:
            str = "<=";
            break;
        case TRI_EQ:
            str = "==";
            break;
        case TRI_NEQ:
            str = "!=";
            break;
        case TRI_CMP:
            str = "cmp";
            break;
        case TRI_CALL:
            str = "call";
            break;
        case TRI_PROC:
            str = "proc";
            break;
        case TRI_ENDP:
            str = "endp";
            break;
        case TRI_JMP:
            str = "jmp";
            break;
        case TRI_RET:
            str = "ret";
            break;
        case TRI_MOV:
            str = "mov";
            break;
        case TRI_SHORT_INT:
            str = "sh->i";
            break;
        case TRI_SHORT_LONG:
            str = "sh->l";
            break;
        case TRI_SHORT_LONGLONG:
            str = "sh->ll";
            break;
        case TRI_INT_LONG:
            str = "i->l";
            break;
        case TRI_INT_LONGLONG:
            str = "i->ll";
            break;
        case TRI_LONG_LONGLONG:
            str = "l->ll";
            break;
        case TRI_LONGLONG_LONG :
            str = "ll->l";
            break;
        case TRI_LONGLONG_INT :
            str = "ll->i";
            break;
        case TRI_LONGLONG_SHORT:
            str = "ll->sh";
            break;
        case TRI_LONG_INT :
            str = "l->i";
            break;
        case TRI_LONG_SHORT:
            str = "l->sh";
            break;
        case TRI_INT_SHORT :
            str = "i->sh";
            break;
        case TRI_NOP:
            str = "nop";
            break;
        case TRI_IF:
            str = "if";
            break;
        case TRI_UNIQUE_LABEL:
            str = getUniqueLabel(4) + ':';
            break;
        default:
            throw invalid_argument("invalid operation code: " + to_string(code));
    }

    return str;
}

void LL1::outOneOperand(Operand *operand) {
    if (operand == nullptr || operand->type == EMPTY)
        cout << "-";
    else if (operand->type == ADDRESS)
        cout << "(" << operand->value.address << ")";
    else if (operand->type == NODE)
        cout << operand->value.node->id;
}

void LL1::outOperands() {
    cout << "Операнды: ";
    for (int i = 0; i < operands.size(); i++) {
        outOneOperand(operands[i]);
        cout << " ";
    }
    cout << "\n";
}


Triad *LL1::getCastTypeTriad(int castableType, int typeToCast, Operand *operandForCast) {
    if (typeToCast == TDataUndefined) {
        sc->printError("Попытка привести к типу TDataUndefined");
    }
    if (castableType == TDataShort) {
        switch (typeToCast) {
            case TDataInt:
                return new Triad(TRI_SHORT_INT, operandForCast, nullptr);
            case TDataLong:
                return new Triad(TRI_SHORT_LONG, operandForCast, nullptr);
            case TDataLongLong:
                return new Triad(TRI_SHORT_LONGLONG, operandForCast, nullptr);
        }
    }
    if (castableType == TDataInt) {
        switch (typeToCast) {
            case TDataShort:
                return new Triad(TRI_INT_SHORT, operandForCast, nullptr);
            case TDataLong:
                return new Triad(TRI_INT_LONG, operandForCast, nullptr);
            case TDataLongLong:
                return new Triad(TRI_INT_LONGLONG, operandForCast, nullptr);
        }
    }
    if (castableType == TDataLong) {
        switch (typeToCast) {
            case TDataShort:
                return new Triad(TRI_LONG_SHORT, operandForCast, nullptr);
            case TDataInt:
                return new Triad(TRI_LONG_INT, operandForCast, nullptr);
            case TDataLongLong:
                return new Triad(TRI_LONG_LONGLONG, operandForCast, nullptr);
        }
    }
    if (castableType == TDataLongLong) {
        switch (typeToCast) {
            case TDataShort:
                return new Triad(TRI_LONGLONG_SHORT, operandForCast, nullptr);
            case TDataInt:
                return new Triad(TRI_LONGLONG_INT, operandForCast, nullptr);
            case TDataLong:
                return new Triad(TRI_LONGLONG_LONG, operandForCast, nullptr);
        }
    }
    sc->printError("Попытка привести TDataUndefined к другому типу");
    return TDataUndefined;
}

int LL1::getTypeDataTriad(Triad *&pTriad) {
    int type1 = getTypeDataOperand(pTriad->getOperand1());
    int type2 = getTypeDataOperand(pTriad->getOperand2());
    return type2 > type1 ? type2 : type1;
}

int LL1::getLastTriadAddr() const {
    return triads.size() - 1;
}

string LL1::getUniqueLabel(int len) {
    {
        std::string tmp_s;
        static const char alphanum[] =
                "0123456789"
                "abcdefghijklmnopqrstuvwxyz";

        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i)
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


        return tmp_s;
    }
}
