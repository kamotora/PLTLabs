#include "Triad.h"

Operand::Operand(int triadNum) {
    this->type = ADDRESS;
    this->value.address = triadNum;
}

Operand::Operand(Node *operand) {
    this->type = NODE;
    this->value.node = operand;
}

Operand::Operand(TypeLex operand) : Operand(new Node(operand)) {}

bool Operand::equals(Operand *other) {
    if (other == nullptr || this->type != other->type)
        return false;
    if (this->type == ADDRESS && this->value.address == other->value.address)
        return true;
    if (this->type == NODE && strcmp(this->value.node->id, other->value.node->id) == 0)
        return true;
    return false;
}

bool Operand::anyEquals(const std::list<Operand *> &operands) {
    for (const auto &item : operands)
        if (equals(item))
            return true;
    return false;
}

Triad::Triad(int operation, Operand *op1, Operand *op2) : Triad(operation) {
    this->operand1 = op1;
    this->operand2 = op2;
}

Triad::Triad(int operation) {
    if (operation > GEN_PUSH)
        throw InvalidGenFuncError(operation);
    this->operation = operation;
}

int Triad::getOperation() const {
    return operation;
}

Operand *Triad::getOperand1() const {
    return operand1;
}

Operand *Triad::getOperand2() const {
    return operand2;
}

void Triad::setOperand1(Operand *pOperand) {
    Triad::operand1 = pOperand;
}

void Triad::setOperand2(Operand *pOperand) {
    Triad::operand2 = pOperand;
}

Triad::~Triad() {
    if (operand1 != nullptr)
        delete operand1;
    if (operand2 != nullptr)
        delete operand2;
}


