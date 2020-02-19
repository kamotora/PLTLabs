//
// Created by artem on 16.10.2019.
//


#include "Diagram.h"
#include "Tree.h"

bool Diagram::flagInterpret = true;

bool Diagram::flagReturn = false;

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
        sem1(_id, typeData);
        bool isMain = strcmp(_id, "main") == 0;
        if (!isMain) {
            flagInterpret = false;
        } else {
            root->setCur(root->getCur()->getRight());
        }
        sostOper();
        if (!isMain)
            flagInterpret = true;
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
        sem3(lex, typeData);
        tmpUk = sc->getUK();
        t = sc->scanner(lex);

        //Если после идентификатора равно - это присваивание Выражения 1
        if (t == TSave) {
            //--- СЕМ 4 ---//
            Node *res = new Node();
            expression1(res);
            sem4(root->getCur()->getNode(), res);
            sem91();
            delete res;
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
    Node *res = new Node();
    //--- СЕМ 11 особая))---//
    Tree *v = sem11(res, lex);

    t = sc->scanner(lex);
    if (t != TSave)
        sc->printError("Ожидался знак = ", lex);


    //--- end СЕМ 11 ---//
    expression1(res);
    //--- СЕМ 4 ---//
    if (v != nullptr)
        sem4(v->getNode(), res);
    else
        sem4(nullptr, res); // nullptr - метод не должен работать, флаг = false
    //--- end СЕМ 4 ---//
    sem91();
    delete res;
}


void Diagram::sostOper() {
    TypeLex lex;
    int t;
    t = sc->scanner(lex);
    if (t != TLeftFigSkob)
        sc->printError("Ожидался символ {", lex);
    //--- Добавление блока ---//
    Tree *v = nullptr;
    if (flagInterpret)
        v = root->semAddBlock();
    blokSostOper();
    t = sc->scanner(lex);
    if (t != TRightFigSkob)
        sc->printError("Ожидался символ }", lex);
    //--- Назад ---//
    if (flagInterpret || flagReturn) {
        //printf("До удаления блока:\n");
        //outTree();
        //root->setCur(v);
        // --- Удаление блока ---//
        if (v != nullptr) {
            root->setCur(v->delBlock());
            // --- Конец удаления блока ---//
            printf("//////////////////\nДерево после удаления блока\n");
            outTree();
        }
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
        Node *res = new Node();
        if (t != TLeftRoundSkob)
            sc->printError("ожидался символ (", lex);
        assign();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);

        //Запоминмаем, чтобы потом восстановить
        bool localFlag = flagInterpret;
        //Выполняем условие для входа в цикл и проверям его
        sc->getUK(forCondition, forConditionStr, forConditionPos);
        expression1(res);
        sem91();
        checkCondition(res);

        //3 выражение
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("ожидался символ ;", lex);
        sc->getUK(forStepExpression, forStepExpressionStr, forStepExpressionPos);
        //не интерпретируем в 1 проход цикла
        bool memFlag = flagInterpret;
        flagInterpret = false;
        expression1(res);
        sem91();
        //восстанавливаем результат условия цикла
        flagInterpret = memFlag;
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

        expression1(res);
        sem91();

        delete res;
        res = new Node;
        //2 выражение в for
        sc->setUK(forCondition, forConditionStr, forConditionPos);
        expression1(res);
        sem91();
        checkCondition(res);
        //delete res;
        if (flagInterpret) {
            sc->setUK(startBlockFor, startBlockForStr, startBlockForPos);
            goto startBlock;
        } else {
            flagInterpret = localFlag;
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
        sem91();
        t = sc->scanner(lex);
        if (t != TTZpt)
            sc->printError("Ожидался символ ;", lex);
        //--- СЕМ 5 ---//
        sem5(&res2);
        //--- end СЕМ 5 ---//
        return;
    }
    sc->printError("Ожидался оператор", lex);
}

void Diagram::checkCondition(Node *res) {
    if (flagInterpret && (res->dataValue->int32Data != 0)) flagInterpret = 1;
    else flagInterpret = 0;
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
    Node *res1 = new Node();
    while (t == TNEQ || t == TEQ) {
        expression2(res1);
        //--- СЕМ 8 ---//
        sem8Compare(res, res1, t);
        //--- end СЕМ 8 ---//
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
    if (uno == TMinus) {
        if (res->typeData == TDataInt)
            res->dataValue->int32Data *= -1;
        else
            res->dataValue->int64Data *= -1;
    }
    delete res1;
}

void Diagram::expression2(Node *res) {
    expression3(res);
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    Node *res1 = new Node();
    while (t == TGE || t == TGT || t == TLE || t == TLT) {
        expression3(res1);
        // -- СЕМ 8 -- //
        sem8Compare(res, res1, t);
        // --  end СЕМ 8 -- //
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
    delete res1;
}

void Diagram::expression3(Node *res) {
    expression4(res);
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    Node *res1 = new Node();
    while (t == TPlus || t == TMinus) {
        expression4(res1);
        // -- СЕМ 8 -- //
        sem8(res, res1, t);
        //--  end СЕМ 8 -- //
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
    delete res1;
}

void Diagram::expression4(Node *res) {
    expression5(res);
    TypeLex lex;
    int t;
    int tmpUk;
    tmpUk = sc->getUK();
    t = sc->scanner(lex);
    Node *res1 = new Node();
    while (t == TMul || t == TDiv || t == TMod) {
        expression5(res1);
        // -- СЕМ 8 -- //
        sem8(res, res1, t);
        //--  end СЕМ 8 -- //
        tmpUk = sc->getUK();
        t = sc->scanner(lex);
    }
    sc->setUK(tmpUk);
    delete res1;
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
            sem9(res, t);
            return;
        } else {
            sc->setUK(tmpUk);
        }
    } else
        sem9(res, t);
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

//Сем1 - проверка на существование описания функции. Если ранее не описывалась, добавляем в таблицу. Иначе – ошибка
void Diagram::sem1(char *_id, int typeData) {
    if (!flagInterpret)
        return;
    //--- СЕМ 1 ---//
    Tree *v = root->semAddNode(_id, TNodeFunction, typeData, sc);
    int startFuncUk, startFuncLine, startFuncPos;
    sc->getUK(startFuncUk, startFuncLine, startFuncPos);
    v->getNode()->funcPosition = new Position(startFuncUk, startFuncLine, startFuncPos);
    sc->printNum();
    printf("Добавлен идентификатор %s с типом элемента %s и типом данных %s\n", _id, TNodeToName(TNodeFunction),
           TDataToName(typeData).c_str());
    //--- end СЕМ 1 ---//
}


void Diagram::sem3(char *lex, int typeData) {
    if (!flagInterpret)
        return;
    // --- СЕМ 3 ---//
    Tree *v = root->semAddNode(lex, TNodeVar, typeData, sc);
    //sc->printNum();
    //printf("Добавлен идентификатор %s с типом элемента %s и типом данных %s\n",lex,TNodeToName(TNodeVar), TDataToName(typeData));
    //--- end СЕМ 3 ---//
}

void Diagram::sem4(Node *var, Node *resExpress) {
    if (!flagInterpret)
        return;
    int type1 = var->typeData;
    int type2 = resExpress->typeData;
    if (type1 < type2)
        sc->printWarningTypes(type1, type2, WSmallType);
    //if (type1 > type2)
    //    sc->printWarningTypes(type2, type1, WPrivedenie);
    var->init = true;

    //Тут будет присваивание
    switch (var->typeData) {
        case TDataLong:
        case TDataInt:
            switch (resExpress->typeData) {
                case TDataInt:
                    var->dataValue->int32Data = resExpress->dataValue->int32Data;
                    break;
                case TDataLongLong:
                    var->dataValue->int32Data = resExpress->dataValue->int64Data;
                    break;
                default:
                    printf("Ошибка в сем4: тип результата неизвестный = %d\n", resExpress->typeData);
            }
            break;
        case TDataLongLong:
            switch (resExpress->typeData) {
                case TDataInt:
                    var->dataValue->int64Data = resExpress->dataValue->int32Data;
                    break;
                case TDataLongLong:
                    var->dataValue->int64Data = resExpress->dataValue->int64Data;
                    break;
                default:
                    printf("Ошибка в сем4: тип результата неизвестный = %d\n", resExpress->typeData);
            }
            break;
        default:
            printf("Ошибка в сем4: тип переменной неизвестный = %d\n", resExpress->typeData);
    }

    //Вывод нового значения
    sc->printNum();
    printf("%s %s = ", TDataToName(var->typeData).c_str(), var->id);
    if (var->typeData == TDataInt)
        printf("%d\n", var->dataValue->int32Data);
    else
        printf("%lld\n", var->dataValue->int64Data);
}


// Сем5
// Проверка на соответствие типа, возвращаемого функцией и типа выражения 1
// Сохранения значения, возвращаемого функцией
void Diagram::sem5(Node *resExpression1) {
    if (!flagInterpret)
        return;
    Node *func = root->findUp(TNodeFunction)->getNode();

    func->init = true;

    switch (func->typeData) {
        case TDataLong:
        case TDataInt:
            switch (resExpression1->typeData) {
                case TDataLong:
                case TDataInt:
                    func->dataValue->int32Data = resExpression1->dataValue->int32Data;
                    break;
                case TDataLongLong:
                    sc->printWarningTypes(TDataInt, TDataLongLong, WDifferentTypesFunc);
                    func->dataValue->int32Data = resExpression1->dataValue->int64Data;
                    break;
                default:
                    printf("Ошибка в сем5: тип результата неизвестный = %d\n", resExpression1->typeData);
            }
            break;
        case TDataLongLong:
            switch (resExpression1->typeData) {
                case TDataLong:
                case TDataInt:
                    func->dataValue->int64Data = resExpression1->dataValue->int32Data;
                    break;
                case TDataLongLong:
                    func->dataValue->int64Data = resExpression1->dataValue->int64Data;
                    break;
                default:
                    printf("Ошибка в сем5: тип результата неизвестный = %d\n", resExpression1->typeData);
            }
            break;
        default:
            printf("Ошибка в сем5: тип функции неизвестный = %d\n", func->typeData);
    }
    if (flagInterpret) {
        flagInterpret = false;
        flagReturn = true;
    }
}


void Diagram::sem8(Node *res, Node *res1, int typeOperation) {
    if (!flagInterpret)
        return;
    int type1 = res->typeData;
    int type2 = res1->typeData;

    if (type1 == TDataUndefined || type2 == TDataUndefined) {
        res->typeData = TDataUndefined;
    } else {
        /*
        if (type1 < type2) {
            sc->printWarningTypes(type1, type2, WPrivedenie);
            res->typeData = type2;
        }
        if (type1 > type2) {
            sc->printWarningTypes(type2, type1, WPrivedenie);
            res1->typeData = type1;
        }
         */
        //TODO надо ли?
        // -- проверка на инициализацию -- //
        if (!res->init)
            sc->printWarning(WUndefined, res->id);
        if (!res1->init)
            sc->printWarning(WUndefined, res1->id);
        // -- конец проверки на инициализацию -- //
    }
    switch (typeOperation) {
        case TPlus:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int32Data += res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue->int64Data = res->dataValue->int32Data;
                            res->dataValue->int64Data += res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сложение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int64Data += res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue->int64Data += res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сложение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 сложение: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TMinus:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int32Data -= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue->int64Data = res->dataValue->int32Data;
                            res->dataValue->int64Data -= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 вычитание: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int64Data -= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue->int64Data -= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 вычитание: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 вычитание: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TDiv:
            try {
                switch (res->typeData) {
                    case TDataLong:
                    case TDataInt:
                        switch (res1->typeData) {
                            case TDataLong:
                            case TDataInt:
                                if (res1->dataValue->int32Data == 0)
                                    throw 1;
                                res->dataValue->int32Data /= res1->dataValue->int32Data;
                                break;
                            case TDataLongLong:
                                if (res1->dataValue->int64Data == 0)
                                    throw 1;
                                res->typeData = TDataLongLong;
                                res->dataValue->int64Data = res->dataValue->int32Data;
                                res->dataValue->int64Data /= res1->dataValue->int64Data;
                                break;
                            default:
                                printf("Сем8 DIV: неизвестный тип res1 %d\n", res1->typeData);
                        }
                        break;
                    case TDataLongLong:
                        switch (res1->typeData) {
                            case TDataLong:
                            case TDataInt:
                                if (res1->dataValue->int32Data == 0)
                                    throw 1;
                                res->dataValue->int64Data /= res1->dataValue->int32Data;
                                break;
                            case TDataLongLong:
                                if (res1->dataValue->int64Data == 0)
                                    throw 1;
                                res->dataValue->int64Data /= res1->dataValue->int64Data;
                                break;
                            default:
                                printf("Сем8 DIV: неизвестный тип res1 %d\n", res1->typeData);
                        }
                        break;
                    default:
                        printf("Сем8 DIV: неизвестный тип res %d\n", res->typeData);
                }
                break;
            } catch (int ex) {
                sc->printError("Деление на ноль невозможно. Переменная ", res1->id, true);
            }
        case TMul:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int32Data *= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue->int64Data = res->dataValue->int32Data;
                            res->dataValue->int64Data *= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 Mul: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int64Data *= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue->int64Data *= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 Mul: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 Mul: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TMod:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int32Data %= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue->int64Data = res->dataValue->int32Data;
                            res->dataValue->int64Data %= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 MOD: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue->int64Data %= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue->int64Data %= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 MOD: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 MOD: неизвестный тип res %d\n", res->typeData);
            }
            break;
        default:
            printf("Сем8 MOD: неизвестный тип операции %d\n", typeOperation);
    }
}

void Diagram::sem8Compare(Node *res, Node *res1, int typeOperation) {
    if (!flagInterpret)
        return;
    int result = 0;
    switch (typeOperation) {
        case TEQ:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int32Data == res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int32Data == res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int64Data == res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int64Data == res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 сравнение: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TNEQ:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int32Data != res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int32Data != res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int64Data != res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int64Data != res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 сравнение: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TGE:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int32Data >= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int32Data >= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int64Data >= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int64Data >= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 сравнение: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TGT:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int32Data > res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int32Data > res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int64Data > res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int64Data > res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 сравнение: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TLE:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int32Data <= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int32Data <= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int64Data <= res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int64Data <= res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 сравнение: неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TLT:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int32Data < res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int32Data < res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue->int64Data < res1->dataValue->int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue->int64Data < res1->dataValue->int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                default:
                    printf("Сем8 сравнение: неизвестный тип res %d\n", res->typeData);
            }
            break;
        default:
            printf("Сем8 сравнение: неизвестный тип операции %d\n", typeOperation);
    }

    res->typeData = TDataInt;
    //res->typeNode = TNodeVar;
    res->dataValue->int32Data = result;
}

// Если константа, выполнить ++ или - - нельзя.
void Diagram::sem9(Node *res, int typeOperation) {
    if (!flagInterpret)
        return;
    if (res->typeNode == TNodeConst)
        sc->printError("Попытка применить операторы ++ или -- к константе");
    switch (typeOperation) {
        case TAddSelf:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    //TODO Обрати внимание
                    root->semGetVar(res->id, sc)->getNode()->dataValue->int32Data++;
                    res->dataValue->int32Data++;
                    break;
                case TDataLongLong:
                    root->semGetVar(res->id, sc)->getNode()->dataValue->int64Data++;
                    res->dataValue->int64Data++;
                    break;
                default:
                    sc->printNum();
                    printf("Ошибка при выполнении ++ или --. Сем9 : неизвестный тип res %d\n", res->typeData);
            }
            break;
        case TSubSelf:
            switch (res->typeData) {
                case TDataLong:
                case TDataInt:
                    res->dataValue->int32Data--;
                    break;
                case TDataLongLong:
                    res->dataValue->int64Data--;
                    break;
                default:
                    printf("Ошибка при выполнении ++ или --. Сем9 : неизвестный тип res %d\n", res->typeData);
            }
            break;
        default:
            printf("Ошибка при выполнении ++ или --. Сем9 : неизвестный тип операции %d\n", typeOperation);
    }
}

void Diagram::sem10(Node *res, TypeLex nameFunc) {
    if (!flagInterpret)
        return;
    Tree *v = root->semGetFunc(nameFunc, sc);
    if (v == nullptr) {
        //res = new Node(TNodeFunction);
    } else {
        res->typeData = v->getNode()->typeData;
        res->init = v->getNode()->init;
    }
    flagReturn = false;
    sc->printNum();
    printf("Вызываем функцию %s\n", nameFunc);
    //Сохраняем текущую позицию по коду
    int saveUk, savePos, saveLine;
    sc->getUK(saveUk, saveLine, savePos);
    //Ставим позицию на начало блока функции
    int funcUk, funcPos, funcLine;
    v->getNode()->funcPosition->getValues(funcUk, funcLine, funcPos);
    sc->setUK(funcUk, funcLine, funcPos);
    //Запоминаем текущий указатель в дереве
    Tree *memCur = root->getCur();
    //Ставим указатель на функцию
    root->setCur(v->getRight());
    sostOper();
    if (flagReturn) {
        flagInterpret = true;
        flagReturn = false;
    }
    //Восстанавливаем указатель
    root->setCur(memCur);
    sc->setUK(saveUk, saveLine, savePos);
    res->dataValue = v->getNode()->dataValue;
}

//Сем11 - Проверка на существование переменной ранее в блоке. Если нет такой - ошибка. Если есть, возвращаем её значение.
Tree *Diagram::sem11(Node *res, TypeLex nameVar) {
    if (!flagInterpret)
        return nullptr;
    Tree *v = root->semGetVar(nameVar, sc);
    if (v == nullptr) {
        //printf("Сюда зайти мы не должны\n");
        return nullptr;
    } else {
        res->typeNode = TNodeVar;
        res->typeData = v->getNode()->typeData;
        res->init = v->getNode()->init;
        strcpy(res->id, v->getNode()->id);
        res->dataValue->int32Data = v->getNode()->dataValue->int32Data;

        res->dataValue->int64Data = v->getNode()->dataValue->int64Data;
    }
    return v;
}

// Вернуть тип константы (int, long, long long, short)
void Diagram::sem12(Node *res, TypeLex lexConst, int typeConst) {
    if (!flagInterpret)
        return;
    long long constanta = (typeConst == TConst10) ? strtoull(lexConst, nullptr, 10) : strtoull(lexConst, nullptr, 16);
    res->typeData = sc->getTypeConst(constanta, typeConst);
    res->typeNode = TNodeConst;
    res->init = true;
    if (res->typeData == TDataInt)
        res->dataValue->int32Data = constanta;
    else
        res->dataValue->int64Data = constanta;
}


void Diagram::outTree() {
    sc->printNum();
    printf("\n");
    root->printTree();
}

bool Diagram::isFlagInterpret() {
    return flagInterpret;
}

void Diagram::setFlagInterpret(bool flagInterpret) {
    Diagram::flagInterpret = flagInterpret;
}


//Выполнение постфиксных ++ или --
void Diagram::sem91() {
    //Забить
    return;
    if (!postfixOper.empty()) {
        for (int i = 0; i < postfixOper.size(); i++)
            sem9(postfixOper[i].first, postfixOper[i].second);
        postfixOper.clear();
    }
}
