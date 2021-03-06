//
// Created by artem on 30.10.2019.
//

#ifndef COMPC___TREE_H
#define COMPC___TREE_H

#include "defs.h"
#include "Scanner.h"
#include <memory>

union DataValue {
    int int32Data;
    long long int64Data;
};

struct Position {
    int uk;
    int line;
    int pos;

    Position() {}

    Position(int _uk, int _line, int _pos) {
        uk = _uk;
        line = _line;
        pos = _pos;
    }

    void getValues(int &_uk, int &_line, int &_pos) {
        _uk = uk;
        _line = line;
        _pos = pos;
    }
};

struct Node {
    // пустой, переменная, функция
    int typeNode;
    TypeLex id;
    // тип (int,short, long, long long)
    int typeData;
    DataValue dataValue; // значение
    Position funcPosition;
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
        //funcPosition = new Position();
    }

    Node(int typeNode, const char *_id, int typeData, const Position &funcPosition) :
            typeNode(typeNode), typeData(typeData), funcPosition(funcPosition) {
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

    ~Tree();

    //Создать левого потомка от текущей вершины this
    void setLeft(Node *data);

    //Создать правого потомка от текущей вершины this
    void setRight(Node *data);

    //Найти элемент от заданной вершины from до корня
    static Tree *findUp(Tree *from, TypeLex id);

    //Найти элемент от текущей вершины до корня
    Tree *findUp(TypeLex id);

    // поиск прямых потомков заданной вершины from
    static Tree *findRightLeft(Tree *from, TypeLex id);

    // поиск прямых потомков текущей вершины this
    Tree *findRightLeft(TypeLex id);

    // поиск данных в дереве от заданной вершины from на одном уровне вложенности
    static Tree *findUpOneLevel(Tree *from, TypeLex id);

    void printTree();

    // ------------------------ Семантические подпрограммы ------------------------

    static void setCur(Tree *a);

    static Tree *getCur();

    // проверка идентификатора на повторное описание внутри блока
    int dupControl(Tree *addr, TypeLex id);

    static void semSetTypeData(Tree *addr, int typeData);

    static void semSetTypeNode(Tree *addr, int typeNode);

    // найти в таблице переменную с именем а (сем11)
    Tree *semGetVar(TypeLex a, Scanner *sc);

    // найти в таблице функцию с именем а (сем10)
    Tree *semGetFunc(char *a, Scanner *sc);

    // Добавить переменную или функцию (сем1),(сем3)
    Tree *semAddNode(char *id, int typeNode, int typeData, Scanner *sc);

    Tree *semAddNode(Node *node);

    Tree *semAddBlock();

    Node *getNode() const;

    static Tree *findUp(int typeNode);

    Tree *getUp() const;

    Tree *getLeft() const;

    Tree *getRight() const;

    static void FreeTree(Tree *tree);

    Tree *findPlaceForDupFunc(Tree *root);

    void delBlock(Tree *tree, bool itsFunc);
};


#endif //COMPC___TREE_H
