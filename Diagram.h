//
// Created by artem on 16.10.2019.
//

#ifndef COMPC___DIAGRAM_H
#define COMPC___DIAGRAM_H

#include "Scanner.h"


class Diagram {
private:
    Scanner *sc;
public:
    Diagram(Scanner * s) {sc=s;}
    //Программа
    void prog();
    //Описание
    void description();
    //Данные
    void data();
    //Тип
    void type();
    //Список
    void list();
    //Переменная
    void var();
    //Присваивание
    void assign();
    //Составной оператор
    void sostOper();
    //Блок составного оператора
    void blokSostOper();
    //Оператор
    void oper();
    //Return
    void myReturn();
    //For
    void myFor();
    //Выражение 1
    void expression1();
    //Выражение 2
    void expression2();
    //Выражение 3
    void expression3();
    //Выражение 4
    void expression4();
    //Выражение 5
    void expression5();
    //Выражение 6
    void expression6();

};


#endif //COMPC___DIAGRAM_H
