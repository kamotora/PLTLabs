//
// Created by kamotora on 16.03.2021.
//

#ifndef COMPC___EMPTYCOLLECTIONERROR_H
#define COMPC___EMPTYCOLLECTIONERROR_H

#include <iostream>
#include <exception>

using namespace std;


class EmptyCollectionError : public invalid_argument {
public:
    EmptyCollectionError(string collectionName) : invalid_argument(
            "Попытка получить элемент из пустой коллекции " + collectionName) {
    }
};


#endif //COMPC___EMPTYCOLLECTIONERROR_H
