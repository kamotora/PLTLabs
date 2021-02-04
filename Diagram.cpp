#include "Diagram.h"


void Diagram::prog() {
    semant->root->setCur(semant->root);
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
    } else
        printf("Синтаксических ошибок не обнаружено. \n");
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
        semant->sem1(_id, typeData);
        bool isMain = strcmp(_id, "main") == 0;
        if (!isMain) {
            semant->setFlagInterpret(false);
        } else {
            semant->root->setCur(semant->root->getCur()->getRight());
        }
        sostOper();
        if (!isMain)
            semant->setFlagInterpret(true);
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
        semant->sem3(lex, typeData);
        tmpUk = sc->getUK();
        t = sc->scanner(lex);

        //Если после идентификатора равно - это присваивание Выражения 1
        if (t == TSave) {
            //--- СЕМ 4 ---//
            Node res;
            expression1(&res);
            semant->sem4(semant->root->getCur()->getNode(), &res);
            semant->sem91();
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
    Node res;
    //--- СЕМ 11 особая))---//
    Tree *v = semant->sem11(&res, lex);

    t = sc->scanner(lex);
    if (t != TSave)
        sc->printError("Ожидался знак = ", lex);


    //--- end СЕМ 11 ---//
    expression1(&res);
    //--- СЕМ 4 ---//
    if (v != nullptr)
        semant->sem4(v->getNode(), &res);
    else
        semant->sem4(nullptr, &res); // nullptr - метод не должен работать, флаг = false
    //--- end СЕМ 4 ---//
    //sem91();
}


void Diagram::sostOper() {
    TypeLex lex;
    int t;
    t = sc->scanner(lex);
    if (t != TLeftFigSkob)
        sc->printError("Ожидался символ {", lex);
    //--- Добавление блока ---//
    Tree *v = nullptr;
    if (semant->isFlagInterpret())
        v = semant->root->semAddBlock();
    blokSostOper();
    t = sc->scanner(lex);
    if (t != TRightFigSkob)
        sc->printError("Ожидался символ }", lex);
    // --- Удаление блока ---//
    if (v != nullptr) {
        semant->root->delBlock(v, false);
    }
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
        } else
            sc->printError("Ожидался символ ;", lex);
    }
    if (t == TTZpt) {
        //Пустой оператор
        return;
    }
    int forCondition, forStepExpression, startBlockFor, endFor;
    //Для запоминания строки и позиции в ней, шобы потом восстановить
    int forConditionStr, forConditionPos, forStepExpressionStr, forStepExpressionPos, startBlockForStr, startBlockForPos, endForStr, endForPos;
    if (t == TFor) {
        t = sc->scanner(lex);
        Node res;
        if (t != TLeftRoundSkob)
            sc->printError("ожидался символ (", lex);
        assign();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);

        //Запоминмаем, чтобы потом восстановить
        bool localFlag = semant->isFlagInterpret();
        //Выполняем условие для входа в цикл и проверям его
        sc->getUK(forCondition, forConditionStr, forConditionPos);
        expression1(&res);
        //sem91();
        semant->checkCondition(&res);

        //3 выражение
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);
        sc->getUK(forStepExpression, forStepExpressionStr, forStepExpressionPos);
        //не интерпретируем в 1 проход цикла
        bool memFlag = semant->isFlagInterpret();
        semant->setFlagInterpret(false);
        expression1(&res);
        //sem91();
        //восстанавливаем результат условия цикла
        semant->setFlagInterpret(memFlag);
        t = sc->scanner(lex);
        if (t != TRightRoundSkob)
            sc->printError("ожидался символ )", lex);
        //Начало блока for
        sc->getUK(startBlockFor, startBlockForStr, startBlockForPos);
        startBlock:
        oper();
        sc->getUK(endFor, endForStr, endForPos);
        //3 выражение в for
        sc->setUK(forStepExpression, forStepExpressionStr, forStepExpressionPos);

        expression1(&res);
        //sem91();

        Node res1;
        //2 выражение в for
        sc->setUK(forCondition, forConditionStr, forConditionPos);
        expression1(&res1);
        //sem91();
        semant->checkCondition(&res1);
        if (semant->isFlagInterpret()) {
            sc->setUK(startBlockFor, startBlockForStr, startBlockForPos);
            goto startBlock;
        } else {
            //Восстанавливаем флаг. Если был возврат, то дальше интерп не надо
            semant->setFlagInterpret(localFlag && !semant->isFlagReturn());
            sc->setUK(endFor, endForStr, endForPos);
        }
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
        //sem91();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("Ожидался символ ;", lex);
        //--- СЕМ 5 ---//
        semant->sem5(&res2);
        //--- end СЕМ 5 ---//
        return;
    }
    sc->printError("Ожидался оператор", lex);
}


void Diagram::expression1(Node *res) {
    TypeLex lex;
    int t, uno;
    int tmpUk;
    tmpUk = sc->getUK();
    uno = sc->scanner(lex);
    if (uno == TPlus || uno == TMinus) {
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
        semant->sem8Compare(res, &res1, t);
        //--- end СЕМ 8 ---//
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
    if (uno == TMinus) {
        if (res->typeData == TDataInt)
            res->dataValue.int32Data *= -1;
        else
            res->dataValue.int64Data *= -1;
    }
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
        semant->sem8Compare(res, &res1, t);
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
        semant->sem8(res, &res1, t);
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
        semant->sem8(res, &res1, t);
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
        //sem9(res, t);
        //--  end СЕМ 9 -- //
    } else
        sc->setUK(tmpUk);
    expression6(res);
    if (!isPref) {
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
        if (t == TAddSelf || t == TSubSelf) {
            //postfixOper.push_back(std::make_pair(res, t));
            semant->sem9(res, t);
            return;
        } else {
            sc->setUK(tmpUk);
        }
    } else
        semant->sem9(res, t);
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
            semant->sem11(res, _id);
            //sc->printNum();
            //printf("Найдено использование %s с типом элемента %s и типом данных %s\n",_id,TNodeToName(v->getNode()->typeNode), TDataToName(v->getNode()->typeData));

        }
        return;
    }

    if (t == TConst16) {
        // -- СЕМ 12 -- //
        semant->sem12(res, lex, t);
        // -- end СЕМ 12 -- //
        return;
    }
    if (t == TConst10) {
        // -- СЕМ 12 -- //
        semant->sem12(res, lex, t);
        // -- end СЕМ 12 -- //
        return;
    }
}

void Diagram::setSemant(Semant *pSemant) {
    this->semant = pSemant;
}


void Diagram::sem10(Node *res, TypeLex nameFunc) {
    if (!semant->isFlagInterpret())
        return;
    Tree *v = semant->root->semGetFunc(nameFunc, sc);
    if (v == nullptr) {
        //res = new Node(TNodeFunction);
    } else {
        res->typeData = v->getNode()->typeData;
        res->init = v->getNode()->init;
    }
    semant->setFlagReturn(false);
    sc->printNum();
    printf("Вызываем функцию %s\n", nameFunc);
    //Сохраняем текущую позицию по коду
    int saveUk, savePos, saveLine;
    sc->getUK(saveUk, saveLine, savePos);
    //Ставим позицию на начало блока функции
    int funcUk, funcPos, funcLine;
    v->getNode()->funcPosition.getValues(funcUk, funcLine, funcPos);
    sc->setUK(funcUk, funcLine, funcPos);
    //Создаём дубль заголовка функции для обеспечения рекурсии
    //Она должна быть в глобальной области видимости для доступа к глобальным переменным
    //Запоминаем текущий указатель в дереве
    Tree *memCur = semant->root->getCur();
    // cur - самое лево
    semant->root->setCur(semant->root->findPlaceForDupFunc(semant->root));
    // Дублируем заголовок
    Tree *dupFunc = semant->root->semAddNode(v->getNode());
    //Ставим указатель на тело функции
    semant->root->setCur(dupFunc->getRight());
    //sostOper
    sostOper();
    if (semant->isFlagReturn()) {
        semant->setFlagInterpret(true);
        semant->setFlagReturn(false);
    }
    //Восстанавливаем указатель
    semant->root->setCur(memCur);
    res->dataValue = dupFunc->getNode()->dataValue;
    //Удаляем остатки функции
    semant->root->delBlock(dupFunc, true);
    sc->setUK(saveUk, saveLine, savePos);
}
