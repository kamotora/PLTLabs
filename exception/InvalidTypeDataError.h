#ifndef COMPC___INVALIDTYPEDATAERROR_H
#define COMPC___INVALIDTYPEDATAERROR_H

#include <iostream>
#include <exception>

using namespace std;

class InvalidTypeDataError : public invalid_argument {
public:
    InvalidTypeDataError(int invalidTypeData) : invalid_argument(
            "incorrect type data: " + to_string(invalidTypeData)) {
    }
};


#endif //COMPC___INVALIDTYPEDATAERROR_H
