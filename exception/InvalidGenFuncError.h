#ifndef COMPC___INVALIDGENFUNCERROR_H
#define COMPC___INVALIDGENFUNCERROR_H

#include <iostream>
#include <exception>

using namespace std;

class InvalidGenFuncError : public invalid_argument {
public:
    InvalidGenFuncError(int invalidTypeNum) : invalid_argument(
            "incorrect operation num, see defs GEN_*** : " + to_string(invalidTypeNum)) {
    }
};


#endif //COMPC___INVALIDGENFUNCERROR_H
