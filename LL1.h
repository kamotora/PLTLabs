#ifndef COMPC___LL1_H
#define COMPC___LL1_H

#include "defs.h"
#include "Tree.h"
#include <iostream>

using namespace std;

class LL1 {
private:
    int magazin[MAX_MAG];
    // указатель верхушки магазина
    int z = 0;

    Scanner *sc;
    Tree *root;  // корень семантического дерева

    int currentType;  // последний отсканированный тип
    TypeLex currentId;  // посдедний отсканированный идентификатор

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
};


#endif //COMPC___LL1_H
