#ifndef COMPC___SEMANT_H
#define COMPC___SEMANT_H

#include "Tree.h"
#include "Scanner.h"
#include "defs.h"

class Semant {
private:
    static bool flagInterpret, flagReturn;
    Scanner *sc;
public:
    Tree *root = new Tree();

    Semant(Scanner *s) { sc = s; }

    void sem1(char *_id, int typeData);

    void sem3(char *lex, int typeData);

    void sem4(Node *var, Node *resExpress);

    void sem5(Node *resExpression1);

    void sem8(Node *res, Node *res1, int typeOperation);

    void sem8Compare(Node *res, Node *res1, int typeOperation);

    void sem9(Node *res, int typeOperation);

    //void sem10(Node *res, char *nameFunc);

    void sem10(Node *res, char *nameFunc);

    void sem12(Node *res, char *lexConst, int typeConst);

    void outTree();

    bool isFlagInterpret();

    void setFlagInterpret(bool flagInterpret);

    void sem91();

    void checkCondition(Node *res);

    bool isFlagReturn();

    Tree *sem11(Node *res, char *nameVar);

    void *sem10AfterWork(Node *res);

    void setFlagReturn(bool b);
};


#endif //COMPC___SEMANT_H
