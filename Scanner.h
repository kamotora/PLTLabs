//
// Created by artem on 02.10.2019.
//

#ifndef COMPC___SCANNER_H
#define COMPC___SCANNER_H

#include "defs.h"

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

    void printWarning(const std::string &error);

    void setPos(int _pos);

    int getPos();

    void setUK(int i);

    void setLine(int _line);

    int getLine();

    void printError(const std::string &error);

    void printError(std::string error, char *lex);

    void printError(std::string error, char *lex, bool needExit);

    void printNum();

    int getTypeConst(char *lex, int typeConst, bool isShort = false);

    void printWarningTypes(int type1, int type2, int typeWarning);

    void printWarning(int typeError, char *lex = nullptr);

};
#endif //COMPC___SCANNER_H
