//
// Created by kamotora on 25.03.2020.
//

#include "Semant.h"

bool Semant::flagInterpret = true;

bool Semant::flagReturn = false;

//Сем1 - проверка на существование описания функции. Если ранее не описывалась, добавляем в таблицу. Иначе – ошибка
void Semant::sem1(char *_id, int typeData) {
    if (!flagInterpret)
        return;
    //--- СЕМ 1 ---//
    Tree *v = root->semAddNode(_id, TNodeFunction, typeData, sc);
    int startFuncUk, startFuncLine, startFuncPos;
    sc->getUK(startFuncUk, startFuncLine, startFuncPos);
    v->getNode()->funcPosition = Position(startFuncUk, startFuncLine, startFuncPos);
    //sc->printNum();
    //printf("Добавлен идентификатор %s с типом элемента %s и типом данных %s\n", _id, TNodeToName(TNodeFunction),TDataToName(typeData).c_str());
    //--- end СЕМ 1 ---//
}

void Semant::sem3(char *lex, int typeData) {
    if (!flagInterpret)
        return;
    // --- СЕМ 3 ---//
    Tree *v = root->semAddNode(lex, TNodeVar, typeData, sc);
    //printf("Добавлен идентификатор %s с типом элемента %s и типом данных %s\n",lex,TNodeToName(TNodeVar), TDataToName(typeData).c_str());
    //--- end СЕМ 3 ---//
}

void Semant::sem4(Node *var, Node *resExpress) {
    if (!flagInterpret)
        return;
    if (var->typeNode != TNodeVar) {
        sc->printError("Попытка присвоить значение не переменной", var->id);
    }
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
                    var->dataValue.int32Data = resExpress->dataValue.int32Data;
                    break;
                case TDataLongLong:
                    var->dataValue.int32Data = resExpress->dataValue.int64Data;
                    break;
                default:
                    printf("Ошибка в сем4: тип результата неизвестный = %d\n", resExpress->typeData);
            }
            break;
        case TDataLongLong:
            switch (resExpress->typeData) {
                case TDataInt:
                    var->dataValue.int64Data = resExpress->dataValue.int32Data;
                    break;
                case TDataLongLong:
                    var->dataValue.int64Data = resExpress->dataValue.int64Data;
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
        printf("%d\n", var->dataValue.int32Data);
    else
        printf("%lld\n", var->dataValue.int64Data);
}


// Сем5
// Проверка на соответствие типа, возвращаемого функцией и типа выражения 1
// Сохранения значения, возвращаемого функцией
void Semant::sem5(Node *resExpression1) {
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
                    func->dataValue.int32Data = resExpression1->dataValue.int32Data;
                    break;
                case TDataLongLong:
                    sc->printWarningTypes(TDataInt, TDataLongLong, WDifferentTypesFunc);
                    func->dataValue.int32Data = resExpression1->dataValue.int64Data;
                    break;
                default:
                    printf("Ошибка в сем5: тип результата неизвестный = %d\n", resExpression1->typeData);
            }
            break;
        case TDataLongLong:
            switch (resExpression1->typeData) {
                case TDataLong:
                case TDataInt:
                    func->dataValue.int64Data = resExpression1->dataValue.int32Data;
                    break;
                case TDataLongLong:
                    func->dataValue.int64Data = resExpression1->dataValue.int64Data;
                    break;
                default:
                    printf("Ошибка в сем5: тип результата неизвестный = %d\n", resExpression1->typeData);
            }
            break;
        default:
            printf("Ошибка в сем5: тип функции неизвестный = %d\n", func->typeData);
    }
    flagInterpret = false;
    flagReturn = true;
}


void Semant::sem8(Node *res, Node *res1, int typeOperation) {
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
        //if (!res->init)
        //sc->printWarning(WUndefined, res->id);
        //if (!res1->init)
        //    sc->printWarning(WUndefined, res1->id);
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
                            res->dataValue.int32Data += res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue.int64Data = res->dataValue.int32Data;
                            res->dataValue.int64Data += res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 сложение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue.int64Data += res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue.int64Data += res1->dataValue.int64Data;
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
                            res->dataValue.int32Data -= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue.int64Data = res->dataValue.int32Data;
                            res->dataValue.int64Data -= res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 вычитание: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue.int64Data -= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue.int64Data -= res1->dataValue.int64Data;
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
                                if (res1->dataValue.int32Data == 0)
                                    throw 1;
                                res->dataValue.int32Data /= res1->dataValue.int32Data;
                                break;
                            case TDataLongLong:
                                if (res1->dataValue.int64Data == 0)
                                    throw 1;
                                res->typeData = TDataLongLong;
                                res->dataValue.int64Data = res->dataValue.int32Data;
                                res->dataValue.int64Data /= res1->dataValue.int64Data;
                                break;
                            default:
                                printf("Сем8 DIV: неизвестный тип res1 %d\n", res1->typeData);
                        }
                        break;
                    case TDataLongLong:
                        switch (res1->typeData) {
                            case TDataLong:
                            case TDataInt:
                                if (res1->dataValue.int32Data == 0)
                                    throw 1;
                                res->dataValue.int64Data /= res1->dataValue.int32Data;
                                break;
                            case TDataLongLong:
                                if (res1->dataValue.int64Data == 0)
                                    throw 1;
                                res->dataValue.int64Data /= res1->dataValue.int64Data;
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
                            res->dataValue.int32Data *= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue.int64Data = res->dataValue.int32Data;
                            res->dataValue.int64Data *= res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 Mul: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue.int64Data *= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue.int64Data *= res1->dataValue.int64Data;
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
                            res->dataValue.int32Data %= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->typeData = TDataLongLong;
                            res->dataValue.int64Data = res->dataValue.int32Data;
                            res->dataValue.int64Data %= res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 MOD: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            res->dataValue.int64Data %= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            res->dataValue.int64Data %= res1->dataValue.int64Data;
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

void Semant::sem8Compare(Node *res, Node *res1, int typeOperation) {
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
                            result = res->dataValue.int32Data == res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int32Data == res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue.int64Data == res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int64Data == res1->dataValue.int64Data;
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
                            result = res->dataValue.int32Data != res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int32Data != res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue.int64Data != res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int64Data != res1->dataValue.int64Data;
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
                            result = res->dataValue.int32Data >= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int32Data >= res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue.int64Data >= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int64Data >= res1->dataValue.int64Data;
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
                            result = res->dataValue.int32Data > res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int32Data > res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue.int64Data > res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int64Data > res1->dataValue.int64Data;
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
                            result = res->dataValue.int32Data <= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int32Data <= res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue.int64Data <= res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int64Data <= res1->dataValue.int64Data;
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
                            result = res->dataValue.int32Data < res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int32Data < res1->dataValue.int64Data;
                            break;
                        default:
                            printf("Сем8 сравнение: неизвестный тип res1 %d\n", res1->typeData);
                    }
                    break;
                case TDataLongLong:
                    switch (res1->typeData) {
                        case TDataLong:
                        case TDataInt:
                            result = res->dataValue.int64Data < res1->dataValue.int32Data;
                            break;
                        case TDataLongLong:
                            result = res->dataValue.int64Data < res1->dataValue.int64Data;
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
    res->dataValue.int32Data = result;
}

// Если константа, выполнить ++ или - - нельзя.
void Semant::sem9(Node *res, int typeOperation) {
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
                    root->semGetVar(res->id, sc)->getNode()->dataValue.int32Data++;
                    res->dataValue.int32Data++;
                    break;
                case TDataLongLong:
                    root->semGetVar(res->id, sc)->getNode()->dataValue.int64Data++;
                    res->dataValue.int64Data++;
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
                    res->dataValue.int32Data--;
                    break;
                case TDataLongLong:
                    res->dataValue.int64Data--;
                    break;
                default:
                    printf("Ошибка при выполнении ++ или --. Сем9 : неизвестный тип res %d\n", res->typeData);
            }
            break;
        default:
            printf("Ошибка при выполнении ++ или --. Сем9 : неизвестный тип операции %d\n", typeOperation);
    }
}

void Semant::sem10(Node *res, TypeLex nameFunc) {
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
    v->getNode()->funcPosition.getValues(funcUk, funcLine, funcPos);
    sc->setUK(funcUk, funcLine, funcPos);
    //Создаём дубль заголовка функции для обеспечения рекурсии
    //Она должна быть в глобальной области видимости для доступа к глобальным переменным
    //Запоминаем текущий указатель в дереве
    Tree *memCur = root->getCur();
    // cur - самое лево
    root->setCur(root->findPlaceForDupFunc(root));
    // Дублируем заголовок
    Tree *dupFunc = root->semAddNode(v->getNode());
    //Ставим указатель на тело функции
    root->setCur(dupFunc->getRight());
    //TODO sostOper
    //sostOper();
    if (flagReturn) {
        flagInterpret = true;
        flagReturn = false;
    }
    //Восстанавливаем указатель
    root->setCur(memCur);
    res->dataValue = dupFunc->getNode()->dataValue;
    //Удаляем остатки функции
    root->delBlock(dupFunc, true);
    sc->setUK(saveUk, saveLine, savePos);
}


//Сем11 - Проверка на существование переменной ранее в блоке. Если нет такой - ошибка. Если есть, возвращаем её значение.
Tree *Semant::sem11(Node *res, TypeLex nameVar) {
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
        res->dataValue.int32Data = v->getNode()->dataValue.int32Data;

        res->dataValue.int64Data = v->getNode()->dataValue.int64Data;
    }
    return v;
}

// Вернуть тип константы (int, long, long long, short)
void Semant::sem12(Node *res, TypeLex lexConst, int typeConst) {
    if (!flagInterpret)
        return;
    long long constanta = (typeConst == TConst10) ? strtoull(lexConst, nullptr, 10) : strtoull(lexConst, nullptr, 16);
    res->typeData = sc->getTypeConst(constanta, typeConst);
    res->typeNode = TNodeConst;
    res->init = true;
    if (res->typeData == TDataInt)
        res->dataValue.int32Data = constanta;
    else
        res->dataValue.int64Data = constanta;
}


void Semant::outTree() {
    sc->printNum();
    printf("\n");
    root->printTree();
}

bool Semant::isFlagInterpret() {
    return flagInterpret;
}

void Semant::setFlagInterpret(bool flagInterpret) {
    Semant::flagInterpret = flagInterpret;
}


//Выполнение постфиксных ++ или --
void Semant::sem91() {
    //Игнорировать
    return;
    /*
    if (!postfixOper.empty()) {
        for (int i = 0; i < postfixOper.size(); i++)
            sem9(postfixOper[i].first, postfixOper[i].second);
        postfixOper.clear();
    }
     */
}

void Semant::checkCondition(Node *res) {
    if (flagInterpret && (res->dataValue.int32Data != 0)) flagInterpret = 1;
    else flagInterpret = 0;
}

bool Semant::isFlagReturn() {
    return flagReturn;
}

void Semant::setFlagReturn(bool b) {
    flagReturn = b;
}
