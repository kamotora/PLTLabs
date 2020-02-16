//
// Created by artem on 16.10.2019.
//

#ifndef COMPC___DIAGRAM_H
#define COMPC___DIAGRAM_H

#include "Scanner.h"
#include "Tree.h"
#include <iostream>
#include <string>
#include "vector"


class Diagram {
private:
    Scanner *sc;
    static bool flagInterpret;
    std::vector<std::pair<Node *, int>> postfixOper;
public:
    Tree *root = new Tree();

    Diagram(Scanner *s) { sc = s; }

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

    void sem8(Node *res1, Node *res2, int typeOperation);


    void sem10(Node *res, TypeLex nameFunc);

    Tree *sem11(Node *res, char *nameVar);

    void sem12(Node *res, TypeLex lexConst, int typeConst);

    void sem9(Node *res, int typeOperation);

    void sem8Compare(Node *res, Node *res1, int typeOperation);

    void sem5(Node *res);

    void outTree();

    void sem1();

    void sem1(char *_id, int typeData);

    void sem3(TypeLex lex, int data);

    void sem4(Node *var, Node resExpress);

    static bool isFlagInterpret();

    static void setFlagInterpret(bool flagInterpret);

    void sem91();

    void checkCondition(Node *res);

    void sem4(Node *var, Node *resExpress);
};


#endif //COMPC___DIAGRAM_H
