#ifndef COMPC___TREE_H
#define COMPC___TREE_H

#include "defs.h"
#include "Scanner.h"
#include "Node.h"
#include <memory>

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

    Node *getNode() const;

    Tree *getUp() const;

    Tree *getLeft() const;

    Tree *getRight() const;


    // ------------------------ Семантические подпрограммы ------------------------

    // проверка идентификатора на повторное описание внутри блока
    int dupControl(Tree *addr, TypeLex id);

    // найти в таблице переменную с именем а (сем11)
    Tree *semGetVar(TypeLex a, Scanner *sc);

    // найти в таблице функцию с именем а (сем10)
    Tree *semGetFunc(char *a, Scanner *sc);

    // Добавить переменную или функцию (сем1),(сем3)
    Tree *semAddNode(char *id, int typeNode, int typeData, Scanner *sc);

    Tree *semAddBlock();

};


#endif //COMPC___TREE_H
