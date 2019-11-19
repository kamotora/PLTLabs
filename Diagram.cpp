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
        int typeData = type();
        t = sc->scanner(lex);
        TypeLex _id;
        strcpy(_id, lex);
        if (t != TIdent)
            sc->printError("Ожидался идентификатор", lex);
        t = sc->scanner(lex);
        if (t != TLeftRoundSkob)
            sc->printError("Ожидался символ (", lex);
        t = sc->scanner(lex);
        if (t != TRightRoundSkob)
            sc->printError("Ожидался символ )", lex);

        //--- СЕМ 1 ---//
        Tree *v = root->semAddNode(_id, TNodeFunction, typeData, sc);
        //sc->printNum();
        //printf("Добавлен идентификатор %s с типом элемента %s и типом данных %s\n",_id,TNodeToName(TNodeFunction), TDataToName(typeData));
        sostOper();
        root->setCur(v);
        //--- end СЕМ 1 ---//
    }
    else{
      data();
    }

}

void Diagram::data() {
    int typeData = type();
    TypeLex lex;
    int t, tmpUk;
    do {
        t = sc->scanner(lex);
        if (t != TIdent)
            sc->printError("Ожидался идентификатор", lex);
        // --- СЕМ 3 ---//
        Tree *v = root->semAddNode(lex, TNodeVar, typeData, sc);
        //sc->printNum();
        //printf("Добавлен идентификатор %s с типом элемента %s и типом данных %s\n",lex,TNodeToName(TNodeVar), TDataToName(typeData));
        //--- end СЕМ 3 ---//
        tmpUk = sc->getUK();
        t = sc->scanner(lex);

        //Если после идентификатора равно - это присваивание Выражения 1
        if (t == TSave) {
            //--- СЕМ 4 ---//
            Node res;
            res.typeData = v->getNode()->typeData;
            strcpy(res.id, v->getNode()->id);
            expression1(&res);
            int type1 = v->getNode()->typeData;
            int type2 = res.typeData;
            std::string str;
            if (type1 < type2)
                sc->printWarningTypes(type1, type2, WSmallType);
            if (type1 > type2)
                sc->printWarningTypes(type2, type1, WPrivedenie);
            v->getNode()->init = true;
            //--- end СЕМ 4 ---//
        } else
            sc->setUK(tmpUk);
        t = sc->scanner(lex);
    } while (t == TZpt);
    if(t != TTZpt)
        sc->printError("Ожидался символ ;", lex);
}

//--- СЕМ 2 ---//
int Diagram::type() {
    TypeLex l;
    int t, tmpUk;
    t = sc->scanner(l);
    if (t != TLong && t != TInt && t != TShort)
        sc->printError("Ожидался тип данных (long, short или int");
    if (t == TInt)
        //int
        return TDataInt;
    int typeData = -1;
    if (t == TShort) {
        //найден short
        //не выходим, т.к. можем найти int
        typeData = TDataShort;
    }
    if (t == TLong) {
        tmpUk = sc->getUK();
        t = sc->scanner(l);
        typeData = TDataLong;
        if (t == TLong) {
            typeData = TDataLongLong;
        } else
            sc->setUK(tmpUk);
    }
    tmpUk = sc->getUK();
    t = sc->scanner(l);

    if (t == TInt) {
        //short int,long int,long long int
    } else
        //short,long,long long
        sc->setUK(tmpUk);
    if (typeData == -1)
        sc->printError("Ошибка при определении типа данных");
    return typeData;
}

void Diagram::assign() {
    TypeLex lex;
    int t;


    t = sc->scanner(lex);

    if (t != TIdent) {
        sc->printError("Ожидался идентификатор", lex);
    }
    //--- СЕМ 11 особая))---//
    Tree *v = root->semGetVar(lex, sc);
    //sc->printNum();
    //printf("Найдено использование %s с типом элемента %s и типом данных %s\n",lex,TNodeToName(v->getNode()->typeNode), TDataToName(v->getNode()->typeData));
    //--- end СЕМ 11 ---//
    t = sc->scanner(lex);
    if (t != TSave)
        sc->printError("Ожидался знак = ", lex);
    //--- СЕМ 4 ---//
    Node res;
    int type1;
    if (v != nullptr) {
        res.typeData = v->getNode()->typeData;
        strcpy(res.id, v->getNode()->id);
        type1 = v->getNode()->typeData;
        v->getNode()->init = true;
    } else
        type1 = TDataUndefined;
    expression1(&res);
    int type2 = res.typeData;
    if (type1 < type2)
        sc->printWarningTypes(type1, type2, WSmallType);
    if (type1 > type2)
        sc->printWarningTypes(type2, type1, WPrivedenie);
    //--- end СЕМ 4 ---//

}


void Diagram::sostOper() {
    TypeLex lex;
    int t;
    t = sc->scanner(lex);
    if (t != TLeftFigSkob)
        sc->printError("Ожидался символ {", lex);
    //--- Добавление блока ---//
    Tree *v = root->semAddBlock();
    blokSostOper();
    //sc->printNum();
    //printf("Найден блок\n");
    t = sc->scanner(lex);
    if (t != TRightFigSkob)
        sc->printError("Ожидался символ }", lex);
    //--- Назад ---//
    root->setCur(v);
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
        Node res;
        if (t != TLeftRoundSkob)
            sc->printError("ожидался символ (", lex);
        assign();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);
        expression1(&res);
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);
        //TODO: Присваивание или выр1 ?
        expression1(&res);
        t = sc->scanner(lex);
        if (t != TRightRoundSkob)
            sc->printError("ожидался символ )", lex);
        oper();
        return;
    }
    if (t == TLeftFigSkob) {
        sc->setUK(tmpUk);
        sostOper();
        return;
    }
    if (t == TReturn) {
        Node res2;
        expression1(&res2);
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("Ожидался символ ;", lex);
        //--- СЕМ 5 ---//
        sem5(&res2);
        //--- end СЕМ 5 ---//
        return;
    }
    sc -> printError("Ожидался оператор",lex);
}

void Diagram::expression1(Node *res) {
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    if (t == TPlus || t == TMinus) {
        //унарный + -
    } else
        sc->setUK(tmpUk);
    expression2(res);
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    Node res1;
    while (t == TNEQ || t == TEQ) {
        expression2(&res1);
        //--- СЕМ 8 ---//
        sem8Compare(res);
        //--- end СЕМ 8 ---//
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
}

void Diagram::expression2(Node *res) {
    expression3(res);
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    Node res1;
    while (t == TGE || t == TGT || t == TLE || t == TLT) {
        expression3(&res1);
        // -- СЕМ 8 -- //
        sem8Compare(res);
        // --  end СЕМ 8 -- //
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
}

void Diagram::expression3(Node *res) {
    expression4(res);
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    Node res1;
    while (t == TPlus || t == TMinus) {
        expression4(&res1);
        // -- СЕМ 8 -- //
        sem8(res, &res1);
        //--  end СЕМ 8 -- //
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
}

void Diagram::expression4(Node *res) {
    expression5(res);
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    Node res1;
    while (t == TMul || t == TDiv || t == TMod) {
        expression5(&res1);
        // -- СЕМ 8 -- //
        sem8(res, &res1);
        //--  end СЕМ 8 -- //
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
}

void Diagram::expression5(Node *res) {
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    bool isPref = false;
    if (t == TAddSelf || t == TSubSelf) {
        isPref = true;
        // -- СЕМ 9 -- //
        sem9(res);
        //--  end СЕМ 9 -- //
    } else
        sc->setUK(tmpUk);
    expression6(res);
    if(!isPref) {
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
        if (t == TAddSelf || t == TSubSelf) {
            // -- СЕМ 9 -- //
            sem9(res);
            //--  end СЕМ 9 -- //
            return;
        } else
            sc->setUK(tmpUk);
    }
}

void Diagram::expression6(Node *res) {
    TypeLex lex;
    int t;
    t = sc->scanner(lex);
    if (t != TIdent && t != TConst10 && t != TConst16 && t != TLeftRoundSkob) {
        sc->printError("Ожидался идентификатор, констанста, скобка", lex);
    }
    if (t == TLeftRoundSkob) {
        expression1(res);
        t = sc->scanner(lex);
        if (t != TRightRoundSkob)
            sc->printError("Ожидался символ )", lex);
        return;
    }
    if (t == TIdent) {
        TypeLex _id;
        strcpy(_id, lex);
        //Проверка на вызов функции
        int tmpUk = sc->getUK();
        t = sc->scanner(lex);
        if (t == TLeftRoundSkob) {
            t = sc->scanner(lex);
            if (t != TRightRoundSkob)
                sc->printError("Ожидался символ )", lex);
            res->typeNode = TNodeFunction;
            // -- СЕМ 10 -- //
            sem10(res, _id);
            //sc->printNum();
            //printf("Найдено использование %s с типом элемента %s и типом данных %s\n",_id,TNodeToName(v->getNode()->typeNode), TDataToName(v->getNode()->typeData));

        } else {
            sc->setUK(tmpUk);
            // -- СЕМ 11 -- //
            sem11(res, _id);
            //sc->printNum();
            //printf("Найдено использование %s с типом элемента %s и типом данных %s\n",_id,TNodeToName(v->getNode()->typeNode), TDataToName(v->getNode()->typeData));

        }
        return;
    }

    if (t == TConst16) {
        // -- СЕМ 12 -- //
        sem12(res, lex, t);
        // -- end СЕМ 12 -- //
        return;
    }
    if (t == TConst10) {
        // -- СЕМ 12 -- //
        sem12(res, lex, t);
        // -- end СЕМ 12 -- //
        return;
    }
}

// Сем5 – проверка на соответствие типа, возвращаемого функцией и типа выражения 1.
void Diagram::sem5(Node *resExpression1) {

    int type1 = resExpression1->typeData;
    Node *func = root->findUp(TNodeFunction)->getNode();
    int type2 = func->typeData;
    if (type1 != type2) {
        sc->printWarningTypes(type2, type1, WDifferentTypesFunc);
    }
    func->init = true;

}

void Diagram::sem8Compare(Node *res) {
    if (res)
        res->typeData = TDataInt;
}

// Если константа, выполнить ++ или - - нельзя.
void Diagram::sem9(Node *res) {
    if (res->typeNode == TNodeConst)
        sc->printError("Попытка применить операторы ++ или -- к константе");
}

void Diagram::sem10(Node *res, TypeLex nameFunc) {
    Tree *v = root->semGetFunc(nameFunc, sc);
    if (v == nullptr) {
        res = new Node(TNodeFunction);
    } else {
        res->typeData = v->getNode()->typeData;
        res->init = v->getNode()->init;
    }
}


void Diagram::sem11(Node *res, TypeLex nameVar) {
    Tree *v = root->semGetVar(nameVar, sc);
    if (v == nullptr)
        res = new Node(TNodeVar);
    else {
        res->typeNode = TNodeVar;
        res->typeData = v->getNode()->typeData;
        res->init = v->getNode()->init;
        strcpy(res->id, v->getNode()->id);
    }
}

// Вернуть тип константы (int, long, long long, short)
void Diagram::sem12(Node *res, TypeLex lexConst, int typeConst) {
    bool isShort = res->typeData == TDataShort;
    res->typeData = sc->getTypeConst(lexConst, typeConst, isShort);
    res->typeNode = TNodeConst;
    res->init = true;
}

void Diagram::sem8(Node *res1, Node *res2) {
    int type1 = res1->typeData;
    int type2 = res2->typeData;

    if (type1 == TDataUndefined || type2 == TDataUndefined) {
        res1->typeData = TDataUndefined;
    } else {
        if (type1 < type2) {
            sc->printWarningTypes(type1, type2, WPrivedenie);
            res1->typeData = type2;
        }
        if (type1 > type2) {
            sc->printWarningTypes(type2, type1, WPrivedenie);
            res2->typeData = type1;
        }
        // -- проверка на инициализацию -- //
        if (!res1->init)
            sc->printWarning(WUndefined, res1->id);
        if (!res2->init)
            sc->printWarning(WUndefined, res2->id);
        // -- конец проверки на инициализацию -- //
    }

}