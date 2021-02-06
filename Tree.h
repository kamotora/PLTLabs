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
        strcpy(id, "###");
    }

    ~Node() {
    }

    Node(int _typeNode) {
        typeNode = _typeNode;
        typeData = TDataUndefined;
        init = false;
        strcpy(id, "###");
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

    //Создать левого потомка от текущей вершины this
    void setLeft(Node *data);

    //Создать правого потомка от текущей вершины this
    void setRight(Node *data);

    //Найти элемент от заданной вершины from до корня
    static Tree *findUp(Tree *from, TypeLex id);

    Tree *findUp(int typeNode);

    //Найти элемент от текущей вершины до корня
    Tree *findUp(TypeLex id);

    // поиск прямых потомков заданной вершины from
    static Tree *findRightLeft(Tree *from, TypeLex id);

    // поиск прямых потомков текущей вершины this
    Tree *findRightLeft(TypeLex id);

    // поиск данных в дереве от заданной вершины from на одном уровне вложенности
    static Tree *findUpOneLevel(Tree *from, TypeLex id);

    void printTree();

    static void setCur(Tree *a);

    static Tree *getCur();
};


#endif //COMPC___TREE_H
