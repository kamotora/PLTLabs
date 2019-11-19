//
// Created by artem on 17.11.2019.
//

#include "LL1.h"

void LL1::epsilon() {
    //z--;
}

LL1::LL1(Scanner *s) {
    sc = s;
    Node *node = new Node();
    strcpy(node->id, "###");
    root = new Tree(NULL, NULL, NULL, node);
    Tree::cur = root;
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
                sc->printError("неверный символ, ожидался", lex);
                return -1;
            }
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
                        TypeLex lex1;
                        int tmpUk = sc->getUK();
                        int lexems[5];
                        for (int i = 0; i < 5; i++)
                            lexems[i] = sc->scanner(lex1);
                        bool isFunc = false;
                        for (int i = 1; i < 5; i++)
                            if (lexems[i] == TLeftRoundSkob && lexems[i - 1] == TIdent) {
                                isFunc = true;
                                break;
                            }
                        sc->setUK(tmpUk);
                        if (isFunc) {
                            magazin[z++] = netermSostOper;
                            magazin[z++] = TRightRoundSkob;
                            magazin[z++] = TLeftRoundSkob;
                            magazin[z++] = TIdent;
                            magazin[z++] = netermType;
                        } else
                            magazin[z++] = netermData;
                    } else {
                        epsilon();
                    }
                    break;

                case netermType:
                    if (t == TShort) {
                        magazin[z++] = TShort;
                        magazin[z++] = netermType3;
                    } else if (t == TLong) {
                        magazin[z++] = netermType2;
                        magazin[z++] = TLong;
                    } else if (t == TInt) {
                        magazin[z++] = netermType3;
                    } else
                        sc->printError("Неверный символ", lex);
                    break;
                case netermType2:
                    if (t == TLong) {
                        magazin[z++] = netermType3;
                        magazin[z++] = TLong;
                    } else
                        epsilon();
                    break;
                case netermType3:
                    if (t == TInt)
                        magazin[z++] = TInt;
                    else
                        epsilon();
                    break;
                case netermData:
                    if (t == TShort || t == TInt || t == TLong) {
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
                        magazin[z++] = TRightFigSkob;
                        magazin[z++] = netermBlockSostOper;
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
                        magazin[z++] = netermAssign;
                        magazin[z++] = TIdent;
                        magazin[z++] = TLeftRoundSkob;
                        magazin[z++] = TFor;
                    } else if (t == TReturn) {
                        magazin[z++] = TTZpt;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TReturn;
                    } else if (t == TIdent) {
                        magazin[z++] = TTZpt;
                        magazin[z++] = netermAssign;
                        magazin[z++] = TIdent;
                    } else if (t == TLeftFigSkob) {
                        magazin[z++] = netermSostOper;
                    } else if (t == TTZpt)
                        magazin[z++] = TTZpt;
                    else
                        sc->printError("Неверный символ. Ожидался оператор", lex);
                    break;


                case netermExpr1:
                    if (t == TPlus) {
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TPlus;
                    } else if (t == TMinus) {
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TMinus;
                    } else {
                        magazin[z++] = netermExpr11;
                        magazin[z++] = netermExpr2;
                    }
                    //sc->printError("Неверный символ. Ожидались +, -, (, идентификатор, константа, ",lex);
                    break;

                case netermExpr11:
                    if (!expression11(t, lex))
                        sc->printError("Неверный символ. Ожидались ==, !=, ),; ", lex);
                    break;
                case netermExpr2:
                    //if(t == TIdent || t == TConst10 || t == TConst16 || t == TLeftRoundSkob){
                    magazin[z++] = netermExpr21;
                    magazin[z++] = netermExpr3;
                    //} else
                    //   sc->printError("Неверный символ. Ожидались (, идентификатор, константа ",lex);
                    break;

                case netermExpr21:
                    if (!expression21(t, lex))
                        sc->printError("Неверный символ. Ожидались ==, !=, <=,<,>,>=, ),; ", lex);
                    break;
                case netermExpr3:
                    //if(t == TIdent || t == TConst10 || t == TConst16 || t == TLeftRoundSkob){
                    magazin[z++] = netermExpr31;
                    magazin[z++] = netermExpr4;
                    //} else
                    //   sc->printError("Неверный символ. Ожидались (, идентификатор, константа ",lex);
                    break;
                case netermExpr31:
                    if (!expression31(t, lex))
                        sc->printError("Неверный символ. Ожидались +,-, ==, !=, <=,<,>,>=, ),; ", lex);
                    break;
                case netermExpr4:
                    //if(t == TIdent || t == TConst10 || t == TConst16 || t == TLeftRoundSkob){
                    magazin[z++] = netermExpr41;
                    magazin[z++] = netermExpr5;
                    //} else
                    //    sc->printError("Неверный символ. Ожидались (, идентификатор, константа ",lex);
                    break;
                case netermExpr41:
                    if (!expression41(t, lex))
                        sc->printError("Неверный символ. Ожидались *,/,% +,-, ==, !=, <=,<,>,>=, ),; ", lex);
                    break;
                case netermExpr5:
                    if (t == TAddSelf) {
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TAddSelf;
                    } else if (t == TSubSelf) {
                        magazin[z++] = netermExpr6;
                        magazin[z++] = TSubSelf;
                    } else {
                        magazin[z++] = netermExpr51;
                        magazin[z++] = netermExpr6;
                    }
                    //sc->printError("Неверный символ. Ожидались ++,--, (, идентификатор, константа ",lex);
                    break;
                case netermExpr51:
                    if (!expression51(t, lex))
                        //sc->printError("Неверный символ. Ожидались *,/,% +,-, ==, !=, <=,<,>,>=, ),; ",lex);
                        sc->printError("Неверный символ. Ожидались ++,--, ),; ", lex);
                    break;
                case netermExpr6:
                    if (t == TIdent) {
                        magazin[z++] = netermFuncCallOrVar;
                        magazin[z++] = TIdent;
                    } else if (t == TConst16) {
                        magazin[z++] = TConst16;
                    } else if (t == TConst10) {
                        magazin[z++] = TConst10;
                    } else if (t == TLeftRoundSkob) {
                        magazin[z++] = TRightRoundSkob;
                        magazin[z++] = netermExpr1;
                        magazin[z++] = TLeftRoundSkob;
                    } else
                        sc->printError("Неверный символ. Ожидались идентификатор, константа, )", lex);
                    break;
                case netermFuncCallOrVar:
                    if (t == TLeftRoundSkob) {
                        magazin[z++] = TRightRoundSkob;
                        magazin[z++] = TLeftRoundSkob;
                    } else
                        epsilon();
                    //sc->printError("Неверный символ. Ожидался символ (",lex);
                    break;
            }
            z--;
        }
    }
    return 123;
}

bool LL1::expression11(int t, TypeLex lex, int add) {
    if (t == TEQ) {
        magazin[z++] = netermExpr11 + add;
        magazin[z++] = netermExpr2 + add;
        magazin[z++] = TEQ;
    } else if (t == TNEQ) {
        magazin[z++] = netermExpr11 + add;
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
        magazin[z++] = netermExpr3;
        magazin[z++] = TGE;
    } else if (t == TGT) {
        magazin[z++] = netermExpr21 + add;
        magazin[z++] = netermExpr3 + add;
        magazin[z++] = TGT;
    } else if (t == TLE) {
        magazin[z++] = netermExpr21 + add;
        magazin[z++] = netermExpr3 + add;
        magazin[z++] = TLE;
    } else if (t == TLT) {
        magazin[z++] = netermExpr21 + add;
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
        magazin[z++] = netermExpr4 + add;
        magazin[z++] = TPlus;
    } else if (t == TMinus) {
        magazin[z++] = netermExpr31 + add;
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
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TMul;
    } else if (t == TDiv) {
        magazin[z++] = netermExpr41 + add;
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TDiv;
    } else if (t == TMod) {
        magazin[z++] = netermExpr41 + add;
        magazin[z++] = netermExpr5 + add;
        magazin[z++] = TMod;
    } else if (t == TRightRoundSkob || t == TTZpt || t == TZpt)
        epsilon();
    else
        return expression31(t, lex, add + 2);
    return true;
}

bool LL1::expression51(int t, TypeLex lex) {
    if (t == TAddSelf) {
        magazin[z++] = TAddSelf;
    } else if (t == TSubSelf) {
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

    if (t == TShort || t == TInt || t == TLong) {
        currentType = t;
    }

    if (t == TIdent) {
        strcpy(currentId, lex);
    }

}

bool LL1::isTerminal(int t) {
    return t < netermProgram && t >= 0;
}