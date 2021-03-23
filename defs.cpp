#include "defs.h"

TypeLex prolog = "Prolog";
TypeLex epilog = "Epilog";

std::string TDataToName(int TData) {
    switch (TData) {
        case TDataInt :
            return "int";
        case TDataLong :
            return "long";
        case TDataLongLong :
            return "long long";
        case TDataShort :
            return "short";
        case TDataUndefined :
            return "undefined";
        default:
            std::cerr << "invalid data type: " << TData << std::endl;
    }
}


const char *TNodeToName(int TNode) {
    switch (TNode) {
        case TNodeEmpty :
            return "неопределено";
        case TNodeVar :
            return "переменная";
        case TNodeFunction :
            return "функция";
    }
}