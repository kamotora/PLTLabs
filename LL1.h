#ifndef COMPC___LL1_H
#define COMPC___LL1_H

#include "defs.h"
#include "Tree.h"
#include <iostream>
#include <stdlib.h>
#include "stack"
#include "Triad.h"
#include "vector"

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
    vector<pair<int, int>> types; // todo избавиться, т.к. не нужен более

    // флаг описания данных
    bool flagData;
    Scanner *sc;
    Tree *root;  // корень семантического дерева
    int currentTypeData;  // последний отсканированный тип (int, long...)
    int currentTypeNode;  // последний отсканированный тип (идентификатор или константа)
    TypeLex currentIdentOrConst;  // последний идентификатор или константа

    vector<Triad *> triads;  //список сгенерированных триад
    vector<int> funcTriads;  // список адресов триад - описаний функций
    vector<Operand *> operands;  //стек результатов
//    vector<int> returnAddress;
    vector<pair<int, vector<int>>> loopTriads; // стек адресов возврата (триада для for, адреса переходов для данного for)

    bool isDelta(int t);

    bool isGenFunc(int t);

    template<typename T>
    T getTopValue(vector<T> &st, const string &name);

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

    int subTypesStack();

    void pushType(int dataType, int nodeType);

    void pushType(Tree *pTree);

    void processingGenFunc(int t);


    void outOneOperand(Operand *operand);

    void outOneTriad(Triad *triad);

    void outTriads();

    void outOperands();

    string codeOperationToString(int code);

    void generateArithmeticTriad(int operation);

    Operand *getOperand();

    Triad *getCastTypeTriad(int castableType, int typeToCast, Operand *operandForCast);

    int getTypeDataOperand(Operand *operand);

    int getTypeDataTriad(Triad *&pTriad);

    int getLastTriadAddr() const;

    static string getUniqueLabel(int len);
};


#endif //COMPC___LL1_H
