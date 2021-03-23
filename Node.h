//
// Created by kamotora on 13.03.2021.
//

#ifndef COMPC___NODE_H
#define COMPC___NODE_H

#include <memory>
#include "defs.h"
#include "Scanner.h"

//union DataValue {
//    short dataAsShort;
//    int dataAsInt;
//    long dataAsLong;
//    long long dataAsLongLong;
//};
//
//struct Position {
//    int uk;
//    int line;
//    int pos;
//
//    Position() {}
//
//    Position(int _uk, int _line, int _pos) {
//        uk = _uk;
//        line = _line;
//        pos = _pos;
//    }
//
//    void getValues(int &_uk, int &_line, int &_pos) {
//        _uk = uk;
//        _line = line;
//        _pos = pos;
//    }
//};

struct Node {

    // пустой, переменная, функция
    int typeNode;
    TypeLex id;
    // тип (int,short, long, long long)
    int typeData;

    Node() {
        typeNode = TNodeEmpty;
        typeData = TDataUndefined;
        strcpy(id, "###");
    }

    ~Node() {
    }

    Node(TypeLex _id) {
        typeNode = TNodeEmpty;
        typeData = TDataUndefined;
        memcpy(id, _id, strlen(_id) + 1);
    }

    Node(int _typeNode) {
        typeNode = _typeNode;
        typeData = TDataUndefined;
        strcpy(id, "###");
    }

    Node(int _typeNode, TypeLex _id, int _typeData) {
        typeNode = _typeNode;
        typeData = _typeData;
        memcpy(id, _id, strlen(_id) + 1);
    }

//    Node(int typeNode, const char *_id, int typeData, const Position &funcPosition) :
//            typeNode(typeNode), typeData(typeData), funcPosition(funcPosition) {
//        memcpy(id, _id, strlen(_id) + 1);
//    }
};

#endif //COMPC___NODE_H
