//
// Created by artem on 16.10.2019.
//

#ifndef COMPC___DIAGRAM_H
#define COMPC___DIAGRAM_H

#include "Scanner.h"
#include "Tree.h"
#include "Semant.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

class Diagram {
private:
    Scanner *sc;
    Semant *semant;
public:
    Diagram(Scanner *s) {
        sc = s;
    }

    //Программа
    void prog();

    //Описание
    void description();

    //Данные
    void data();

    //Тип
    int type();

    //Присваивание
    void assign();

    //Составной оператор
    void sostOper();

    //Блок составного оператора
    void blokSostOper();

    //Оператор
    void oper();

    //Выражение 1
    void expression1(Node *res);

    //Выражение 2
    void expression2(Node *res);

    //Выражение 3
    void expression3(Node *res);

    //Выражение 4
    void expression4(Node *res);

    //Выражение 5
    void expression5(Node *res);

    //Выражение 6
    void expression6(Node *res);

    void setSemant(Semant *pSemant);

    void sem10(Node *res, char *nameFunc);
};


#endif //COMPC___DIAGRAM_H
