//
// Created by artem on 16.10.2019.
//

#include "Diagram.h"

void Diagram::prog() {
    TypeLex lex;
    int t, tmpUk;

    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    sc->setUK(tmpUk);

    if (t != TInt && t != TLong && t != TShort) {
        sc->printError("ожидался short, long, int", lex);
    }

    while (t == TInt || t == TLong || t == TShort) {
        description();
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
        sc->setUK(tmpUk);
    }

    if (t != TEnd) {
        sc->printError("ожидался short, long, int", lex);
    }
}

void Diagram::description() {
    TypeLex lex; int t;
    int tmpUk = sc -> getUK();
    int lexems[5];
    for(int i = 0; i < 5; i++)
        lexems[i] = sc -> scanner(lex);
    bool isFunc = false;
    for(int i = 2; i < 5; i++)
        if(lexems[i] == TLeftRoundSkob && lexems[i - 1] == TIdent){
            isFunc = true;
            break;
        }
    sc -> setUK(tmpUk);
    if(isFunc){
        type();
        t = sc -> scanner(lex);
        TypeLex mem;
        strcpy(mem,lex);
        if(t != TIdent)
            sc ->printError("Ожидался идентификатор",lex);
        t = sc -> scanner(lex);
        if(t != TLeftRoundSkob)
            sc ->printError("Ожидался символ (",lex);
        t = sc -> scanner(lex);
        if(t != TRightRoundSkob)
            sc ->printError("Ожидался символ )",lex);
        sostOper();
    }
    else{
      data();
    }

}

void Diagram::data() {
    type();
    TypeLex lex;
    int t, tmpUk;
    do {
        tmpUk = sc->getUK();
        int tmpPos = sc->getPos();
        int tmpLine = sc->getLine();
        t = sc->scanner(lex);
        if (t != TIdent)
            sc->printError("Ожидался идентификатор", lex);
        int tmpUk2 = sc->getUK();
        t = sc->scanner(lex);

        //Если после идентификатора равно - это присваивание
        if (t == TSave) {
            sc->setUK(tmpUk);
            sc->setLine(tmpLine);
            sc->setPos(tmpPos);
            assign();
        } else
            sc->setUK(tmpUk2);
        //tmpUk = sc -> getUK();
        t = sc->scanner(lex);
    } while (t == TZpt);
    //sc->setUK(tmpUk);
    //t = sc -> scanner(lex);
    if(t != TTZpt)
        sc->printError("Ожидался символ ;", lex);
}


void Diagram::type() {
    TypeLex l;
    int t, tmpUk;
    t = sc -> scanner(l);
    if(t != TLong && t != TInt && t != TShort)
        sc -> printError("Ожидался тип данных (long, short или int");
    if(t == TInt)
        //int
        return;
    if(t == TShort){
        //найден short
        //не выходим, т.к. можем найти int
    }
    if(t == TLong){
        tmpUk = sc->getUK();
        t = sc -> scanner(l);
        if(t == TLong){
            //long long
        } else
            sc->setUK(tmpUk);
    }
    tmpUk = sc->getUK();
    t = sc -> scanner(l);
    if(t == TInt){
        //short int,long int,long long int
        return;
    } else
        //short,long,long long
        sc->setUK(tmpUk);

}

void Diagram::assign() {
    TypeLex lex;
    int t;

    TypeLex ident;

    t = sc->scanner(lex);

    if (t != TIdent) {
        sc->printError("Ожидался идентификатор", lex);
    }
    t = sc->scanner(lex);
    if(t != TSave)
        sc->printError("Ожидался знак = ",lex);
    expression1();
}


void Diagram::sostOper() {
    TypeLex lex; int t;
    t = sc->scanner(lex);
    if(t != TLeftFigSkob)
        sc->printError("Ожидался символ {", lex);
    blokSostOper();
    t = sc->scanner(lex);
    if(t != TRightFigSkob)
        sc->printError("Ожидался символ }", lex);
}

void Diagram::blokSostOper() {
    TypeLex lex; int t;
    int tmpUk = sc -> getUK();
    t = sc -> scanner(lex);
    while(t == TLong || t == TShort || t == TInt || t == TReturn || t == TFor || t == TTZpt || t == TIdent || t == TLeftFigSkob){
        if(t == TLong || t == TShort || t == TInt){
            sc -> setUK(tmpUk);
            data();
        }else{
            sc -> setUK(tmpUk);
            oper();
        }
        tmpUk = sc -> getUK();
        t = sc -> scanner(lex);
    }
    //Если в последний раз не совпало или вщ не зашли в цикл
    sc -> setUK(tmpUk);
}

void Diagram::oper() {
    TypeLex lex; int t;
    int tmpUk = sc -> getUK();
    t = sc->scanner(lex);
    if(t == TIdent){
        sc->setUK(tmpUk);
        assign();
        t = sc -> scanner(lex);
        if(t == TTZpt) {
            //Пустой оператор
            return;
        }
        else
            sc ->printError("Ожидался символ ;",lex);
    }
    if(t == TTZpt){
        //Пустой оператор
        return;
    }
    if(t == TFor){
        t = sc->scanner(lex);
        if (t != TLeftRoundSkob)
            sc->printError("ожидался символ (", lex);
        assign();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);
        expression1();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);
        //TODO: Присваивание или выр1 ?
        expression1();
        t = sc->scanner(lex);
        if (t != TRightRoundSkob)
            sc->printError("ожидался символ )", lex);
        oper();
        return;
    }
    if(t == TLeftFigSkob){
        sc -> setUK(tmpUk);
        sostOper();
        return;
    }
    if(t == TReturn){
        expression1();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("Ожидался символ ;", lex);
        return;
    }
    sc -> printError("Ожидался оператор",lex);
}

void Diagram::expression1() {
    TypeLex lex; int t;
    int tmpUk;
    tmpUk = sc ->getUK();
    t = sc->scanner(lex);
    if(t == TPlus || t == TMinus){
        //унарный + -
    }else
        sc->setUK(tmpUk);
    expression2();
    tmpUk = sc ->getUK();
    t = sc->scanner(lex);
    while(t == TNEQ || t == TEQ){
        expression2();
        tmpUk = sc ->getUK();
        t = sc->scanner(lex);
    }
    sc -> setUK(tmpUk);
}
void Diagram::expression2() {
    expression3();
    TypeLex lex; int t;
    int tmpUk;
    tmpUk = sc ->getUK();
    t = sc->scanner(lex);
    while(t == TGE || t == TGT || t == TLE || t == TLT){
        expression3();
        tmpUk = sc ->getUK();
        t = sc->scanner(lex);
    }
    sc -> setUK(tmpUk);
}
void Diagram::expression3() {
    expression4();
    TypeLex lex; int t;
    int tmpUk;
    tmpUk = sc ->getUK();
    t = sc->scanner(lex);
    while(t == TPlus || t == TMinus){
        expression4();
        tmpUk = sc ->getUK();
        t = sc->scanner(lex);
    }
    sc -> setUK(tmpUk);
}
void Diagram::expression4() {
    expression5();
    TypeLex lex; int t;
    int tmpUk;
    tmpUk = sc ->getUK();
    t = sc->scanner(lex);
    while(t == TMul || t == TDiv || t == TMod){
        expression5();
        tmpUk = sc ->getUK();
        t = sc->scanner(lex);
    }
    sc -> setUK(tmpUk);
}
void Diagram::expression5() {
    TypeLex lex; int t;
    int tmpUk;
    tmpUk = sc ->getUK();
    t = sc->scanner(lex);
    bool isPref = false;
    if(t == TAddSelf || t == TSubSelf){
        isPref = true;
    }
    else
        sc->setUK(tmpUk);
    expression6();
    if(!isPref){
        tmpUk = sc -> getUK();
        t = sc->scanner(lex);
        if(t == TAddSelf || t == TSubSelf){
            return;
        }
        else
            sc->setUK(tmpUk);
    }
}
void Diagram::expression6() {
    TypeLex lex; int t;
    t = sc->scanner(lex);
    if(t != TIdent && t != TConst10 && t != TConst16 && t != TLeftRoundSkob){
        sc -> printError("Ожидался идентификатор, констанста, скобка",lex);
    }
    if(t == TLeftRoundSkob){
        expression1();
        t = sc->scanner(lex);
        if(t != TRightRoundSkob)
            sc->printError("Ожидался символ )", lex);
        return;
    }
    if(t == TIdent){
        //Проверка на вызов функции
        int tmpUk = sc -> getUK();
        t = sc->scanner(lex);
        if(t == TLeftRoundSkob){
            t = sc -> scanner(lex);
            if(t != TRightRoundSkob)
                sc->printError("Ожидался символ )", lex);
        }
        else
            sc->setUK(tmpUk);
        return;
    }

    if(t == TConst16){
        return;
    }
    if(t == TConst10){
        return;
    }
}
