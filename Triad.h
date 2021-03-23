//
// Created by kamotora on 13.03.2021.
//

#ifndef COMPC___TRIAD_H
#define COMPC___TRIAD_H

#include "Node.h"
#include "defs.h"
#include "exception/InvalidGenFuncError.h"

using namespace std;
enum OperandType {
    NODE, ADDRESS, EMPTY
};

union OperandValue {
    Node *node; // непосредственный операнд - узел дерева
    int address; // номер триады- ссылки
};

struct Operand {
    OperandType type = EMPTY;
    OperandValue value; // непосредственный операнд - узел дерева
public:
    Operand(int triadNum);  //операнд - ссылка на триаду
    Operand(Node *operand); //непосредственный операнд
    Operand(TypeLex operand); //непосредственный операнд
};

class Triad {
private:

    int operation;  //операция
    Operand *operand1, *operand2;
public:
    Triad(int operation, Operand *op1, Operand *op2);

    int getOperation() const;

    Operand *getOperand1() const;

    Operand *getOperand2() const;

    void setOperand1(Operand *operand1);

    void setOperand2(Operand *operand2);

    Triad(int operation);
};


#endif //COMPC___TRIAD_H
