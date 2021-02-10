#ifndef COMPC___LL1_H
#define COMPC___LL1_H

#include "defs.h"
#include "Tree.h"
#include "Semant.h"
#include <iostream>
#include <stdlib.h>
//todo не работает с унарными - и +
using namespace std;

class LL1 {
private:
    int magazin[MAX_MAG];
    // указатель верхушки магазина
    int z = 0;
    // стек указателей на вершины семантического дерева
    Tree *treePointers[MAX_MAG];
    // указатель стека вершин
    int tpz = 0;
    // стек типов
    int types[MAX_MAG];
    // указатель стека типов
    int typz = 0;

    // флаг описания данных
    bool flagData;
    Scanner *sc;
    Tree *root;  // корень семантического дерева
    int currentType;  // последний отсканированный тип
    TypeLex currentIdent;  // идентификатор
    int currentTypeConst;
    TypeLex currentConst;
    bool wasConst = false;
    int typeConst;

public:
    LL1(Scanner *s);

    int LL_1();

    void epsilon();

    void getCurrents(int t, char *lex);

    bool isTerminal(int t);

    bool expression11(int t, char *lex, int add = 0);

    bool expression21(int t, char *lex, int add = 0);

    bool expression31(int t, char *lex, int add = 0);

    bool expression41(int t, char *lex, int add = 0);

    bool expression51(int t, char *lex);

    string codeToString(int code);

    void processingDelta(int delta);

    void outTree();
};


#endif //COMPC___LL1_H
