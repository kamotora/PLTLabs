#include "defs.h"

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
