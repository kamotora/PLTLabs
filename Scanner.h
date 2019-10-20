//
// Created by artem on 02.10.2019.
//

#ifndef COMPC___SCANNER_H
#define COMPC___SCANNER_H

#include "defs.h"
using namespace std;

class Scanner{
private:
    //сканируемый модуль
    TypeMod t;
    int uk;
    int pos,line;
    int tmpPos, tmpLine;
    static bool isDigit10(char ch);
    static bool isLetter(char ch);
    static bool isDigit16(char ch);
public:
    void newLine();
    int getUK();
    int scanner(TypeLex typeLex);
    void getData(const char *);
    Scanner(const char *);
    ~Scanner() = default;

    void printError(int typeError);

    void printWarning(int typeError);

    void setPos(int _pos);

    int getPos();

    void setUK(int i);

    void setLine(int _line);

    int getLine();

    void printError(const string &error);

    void printError(string error, char *lex);
};
#endif //COMPC___SCANNER_H
