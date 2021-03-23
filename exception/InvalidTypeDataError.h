#ifndef COMPC___INVALIDGENFUNCERROR_H
#define COMPC___INVALIDGENFUNCERROR_H

#include <iostream>
#include <exception>

using namespace std;

class InvalidGenFuncError : public invalid_argument {
public:
    InvalidGenFuncError(int invalidTypeData) : invalid_argument(
            "incorrect type data: " + to_string(invalidTypeData)) {
    }
};


#endif //COMPC___INVALIDGENFUNCERROR_H
