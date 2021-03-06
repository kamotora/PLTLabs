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
    int pos,line;
    int tmpPos, tmpLine;
    static bool isDigit10(char ch);
    static bool isLetter(char ch);
    static bool isDigit16(char ch);
public:
    int uk;
    void newLine();
    int getUK();
    int scanner(TypeLex typeLex);
    void getData(const char *);
    Scanner(const char *);
    ~Scanner() = default;

    void printError(int typeError);

    void printWarning(const std::string &error);

    void setUK(int i);

    void printError(const std::string &error);

    void printError(std::string error, char *lex);

    void printNum();

    void printWarningTypes(int type1, int type2, int typeWarning);

    void printWarning(int typeError, char *lex = nullptr);

    int getTypeConst(long long int constanta, int typeConst);

    void setUK(int i, int line, int pos);

    void getUK(int &get_uk, int &get_line, int &get_pos);

    void printError(const std::string &error, bool needExit);

    void printError(std::string error, const char *lex, bool needExit);
};
#endif //COMPC___SCANNER_H
