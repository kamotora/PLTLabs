//
// Created by artem on 30.10.2019.
//

#ifndef COMPC___TREE_H
#define COMPC___TREE_H

#include "defs.h"
#include "Scanner.h"

union DataValue {
    short dataAsShort;
    int dataAsInt;
    long dataAsLong;
    long long dataAsLongLong;
};

struct Node {

    // пустой, переменная, функция
    int typeNode;
    TypeLex id;
    // тип (int,short, long, long long)
    int typeData;
    //DataValue dataValue; // значение
    bool init;


    Node() {
        typeNode = TNodeEmpty;
        typeData = TDataUndefined;
        init = false;
    }

    Node(int _typeNode) {
        typeNode = _typeNode;
        typeData = TDataUndefined;
        init = false;
    }

    Node(int _typeNode, TypeLex _id, int _typeData) {
        typeNode = _typeNode;
        typeData = _typeData;
        init = false;
        memcpy(id, _id, strlen(_id) + 1);
    }
};

class Tree {
private:
    Node *node; // данные таблицы
    Tree *up, *left, *right; // родитель, левый и правый потомок

public:
    static Tree *cur; // текущий элемент дерева

    Tree(Tree *_left, Tree *_right, Tree *_up, Node *_node);

    Tree();

    ~Tree() {}

    //Создать левого потомка от текущей вершины this
    void setLeft(Node *data);

    //Создать правого потомка от текущей вершины this
    void setRight(Node *data);

    //Найти элемент от заданной вершины from до корня
    Tree *findUp(Tree *from, TypeLex id);

    //Найти элемент от текущей вершины до корня
    Tree *findUp(TypeLex id);

    // поиск прямых потомков заданной вершины from
    Tree *findRightLeft(Tree *from, TypeLex id);

    // поиск прямых потомков текущей вершины this
    Tree *findRightLeft(TypeLex id);

    // поиск данных в дереве от заданной вершины from на одном уровне вложенности
    Tree *findUpOneLevel(Tree *from, TypeLex id);

    void printTree();

    // ------------------------ Семантические подпрограммы ------------------------

    void setCur(Tree *a);

    Tree *getCur();

    // проверка идентификатора на повторное описание внутри блока
    int dupControl(Tree *addr, TypeLex id);

    void semSetTypeData(Tree *addr, int typeData);

    void semSetTypeNode(Tree *addr, int typeNode);

    // найти в таблице переменную с именем а (сем11)
    Tree *semGetVar(TypeLex a, Scanner *sc);

    // найти в таблице функцию с именем а (сем10)
    Tree *semGetFunc(char *a, Scanner *sc);

    // Добавить переменную или функцию (сем1),(сем3)
    Tree *semAddNode(char *id, int typeNode, int typeData, Scanner *sc);

    Tree *semAddBlock();

    Node *getNode() const;

    Tree *findUp(int typeNode);
};


#endif //COMPC___TREE_H
