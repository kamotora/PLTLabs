#include "Scanner.h"
#include <cstring>
/**
Программа: главная программа языка С++. Допускается описание функций без параметров, функции возвращают значение.
Типы данных: int ( в том числе  short , long, long long) .
Операции: арифметические, сравнения.
Операторы: присваивания и for простейшей формы .
Операнды:  простые переменные и константы.
Константы: целые в 10   c/c  и 16   c/c .
*/

TypeLex keyWord[MAX_NUM_KEY_WORD] = {"for","int","long","short","return"};
int indexKeyWord[MAX_NUM_KEY_WORD] = {TFor,TInt,TLong,TShort,TReturn};

Scanner::Scanner(const char *fileName){
    getData(fileName);
    uk = 0;
    pos = 0;
    line = 1;
};

bool Scanner::isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

bool Scanner::isDigit10(char ch) {
    return ch >= '0' && ch <= '9';
}

template<typename T>
int getSize(T *mas) {
    int i = 0;
    for (i = 0; i < MAX_LEX && mas[i] != '\0'; i++);
    return i;
}

bool Scanner::isDigit16(char ch) {
    return Scanner::isDigit10(ch) || ((ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'));
}

void Scanner::getData(const char *FileName) {
// ввод файла FileName, который содержит текст исходного модуля
    char aa;
    FILE *in = fopen(FileName, "r");
    if (in == nullptr) {
        printError("Отсутствует входной файл");
        exit(1);
    }
    int i = 0;
    while (!feof(in)) {
        fscanf(in, "%c", &aa);
        if (!feof(in))
            t[i++] = aa;
        if (i >= MAX_TEXT - 1) {
            printError("Слишком большой размер исходного модуля");
            break;
        }
    }
    // приписываем знак ’\0’ в конец текста
    t[i] = '\0';
    fclose(in);
}

void Scanner::printError(const std::string &error) {
    std::cout << "Ошибка! " << error << "\n";
    exit(1);
}

void Scanner::printWarning(const std::string &error) {
    std::cout << "Предупреждение!  Строка " << line << ", позиция " << pos << ": " << error << "\n";
}

void Scanner::printWarningTypes(int type1, int type2, int typeWarning) {
    if (type1 == TDataUndefined || type2 == TDataUndefined)
        return;
    switch (typeWarning) {
        case WPrivedenie :
            std::cout << "Предупреждение!  Строка " << line << ", позиция " << pos << ": " << "Приведение типа "
                      << TDataToName(type1) << " к типу " << TDataToName(type2) << "\n";
            break;
        case WDifferentTypesFunc:
            std::cout << "Предупреждение!  Строка " << line << ", позиция " << pos << ": " << "Несоответствие типа "
                      << TDataToName(type2) << " функции и возвращаемого типа " << TDataToName(type1) << std::endl;
            break;
        case WSmallType:
            std::cout << "Предупреждение!  Строка " << line << ", позиция " << pos << ": " << "Попытка записать в тип "
                      << TDataToName(type1) << " данные типа " << TDataToName(type2)
                      << ". Часть данных может быть утеряна" << std::endl;
            break;
    }
}

void Scanner::printError(std::string error, TypeLex lex) {
    std::cout << "Ошибка! Строка " << line << ", позиция " << pos << ": " << error << " ,найдено  " << lex << "  \n";
    exit(1);
}

void Scanner::printError(std::string error, TypeLex lex, bool needExit) {
    std::cout << "Ошибка! Строка " << line << ", позиция " << pos << ": " << error << " ( " << lex << " ) \n";
    if (needExit)
        exit(1);
}

void Scanner::printNum() {
    std::cout << "Строка " << line << ", позиция " << pos << ": ";
}

void Scanner::printWarning(int typeError, TypeLex lex) {
    printf("Предупреждение!  Строка %d, позиция %d. ", line, pos);
    switch (typeError) {
        case WLongId :
            std::cout << "Слишком длинный идентификатор. Его длина будет ограничена " << MAX_LEX << " символами\n";
            break;
        case WUndefined:
            std::cout << "Использование неинициализированной переменной ";
            if (lex != nullptr)
                std::cout << lex;
            std::cout << std::endl;
            break;
        default:
            printf("Неизвестная ошибка %d\n", typeError);
            break;
    }
}

void Scanner::printError(int typeError) {
    printf("Ошибка! Строка %d, позиция %d. ", line, pos);
    switch (typeError) {
        case EWrongChar :
            printf("Недопустимый символ.\n");
            break;
        case ELongIntConst :
            printf("Слишком длинная целая константа.\n");
            break;
        case EWrongConst16 :
            printf("Неверная константа в 16сс.\n");
            break;
        case EConst10StartFrom0 :
            printf("Константа из нескольких цифр начинается с нуля.\n");
            break;
        default:
            printf("Неизвестная ошибка %d\n",typeError);
            break;
    }
    exit(1);
}

int Scanner::scanner(TypeLex lex)  {
    memset(lex, '\0', MAX_LEX);
    int i = 0;
    //Пропускаем игнорируемые символы
    while (t[uk] == ' ' || t[uk] == '\n' || t[uk] == '\t' || t[uk] == '/') {

        //Пропускаем игнорируемые символы(не комментарии)
        while (t[uk] == ' ' || t[uk] == '\n' || t[uk] == '\t') {
            pos++;
            if (t[uk] == '\n')
                newLine();
            uk++;
        }
        //Пропускаем игнорируемые символы(комментарий однострочный)
        if ((t[uk] == '/') &&  (t[uk + 1] == '/')) {
            uk += 2;
            while (t[uk] != '\n' && t[uk] != '\0')
                uk++;

        } else{
            break;
        }
    }

    if(t[uk] == '\0')
        return TEnd;

    if(isLetter(t[uk])){
        lex[i++] = t[uk++];
        pos++;
        while(isLetter(t[uk]) || isDigit10(t[uk])){
            if(i < MAX_LEX-1){
                lex[i++] = t[uk];
            }
            else if (i == MAX_LEX - 1){
                i++;
                printWarning(WLongId);
            }
            uk++;pos++;
        }
        for (int j = 0; j < MAX_NUM_KEY_WORD; j++) {
            if (strcmp(lex, keyWord[j]) == 0)
                return indexKeyWord[j];
        }

        return TIdent;
    }
    else if (isDigit10(t[uk])){
        //Если начинается с нуля
        if(t[uk] == '0'){
            //Если начинается с "0x 0X", 16cc константа
            if(t[uk+1] == 'x' || t[uk+1] == 'X'){
                uk += 2;
                while(isDigit16(t[uk])){
                    lex[i++] = t[uk++];
                    pos++;
                    if (i > SIZE_MAX_LONGLONG_16) {
                        printError(ELongIntConst);
                        return TErr;
                    }
                }
                //Если после 0x не число
                if(i == 0){
                    printError(EWrongConst16);
                    return TErr;
                }
                return TConst16;
            }
            //Если после 0 ещё цифры
            if(isDigit10(t[uk+1])){
                printError(EConst10StartFrom0);
                return TErr;
            }
            //Константа == 0
            lex[i++] = t[uk++];
            pos++;
            return TConst10;
        }
        else{
            while(isDigit10(t[uk])){
                lex[i++] = t[uk++];
                pos++;
                if (i > SIZE_MAX_LONGLONG_10) {
                    printError(ELongIntConst);
                    return TErr;
                }
            }
            return TConst10;
        }
    }
    else if (t[uk] == '+') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] != '+')
            return TPlus;
        else {
            lex[i++] = t[uk++];
            pos++;
            return TAddSelf;
        }

    }
    else if (t[uk] == '-') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] != '-')
            return TMinus;
        else {
            lex[i++] = t[uk++];
            pos++;
            return TSubSelf;
        }

    } else if (t[uk] == '*') {
        lex[i++] = t[uk++];
        pos++;
        return TMul;

    } else if (t[uk] == '/') {
        lex[i++] = t[uk++];
        pos++;
        return TDiv;

    } else if (t[uk] == '%') {
        lex[i++] = t[uk++];
        pos++;
        return TMod;

    } else if (t[uk] == '=') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] == '='){
            lex[i++] = t[uk++];
            pos++;
            return TEQ;
        }else
            return TSave;

    } else if (t[uk] == '>') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] == '=') {
            lex[i++] = t[uk++];
            pos++;
            return TGE;
        } else
            return TGT;

    } else if (t[uk] == '<') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] == '=') {
            lex[i++] = t[uk++];
            pos++;
            return TLE;
        } else
            return TLT;

    } else if (t[uk] == '!') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] == '=') {
            lex[i++] = t[uk++];
            pos++;
            return TNEQ;
        } else {
            printError(EWrongChar);
            return TErr;
        }

    } else if (t[uk] == '(') {
        lex[i++] = t[uk++];
        pos++;
        return TLeftRoundSkob;

    } else if (t[uk] == ')') {
        lex[i++] = t[uk++];
        pos++;
        return TRightRoundSkob;

    } else if (t[uk] == '{') {
        lex[i++] = t[uk++];
        pos++;
        return TLeftFigSkob;

    } else if (t[uk] == '}') {
        lex[i++] = t[uk++];
        pos++;
        return TRightFigSkob;
    }else if (t[uk] == ',') {
        lex[i++] = t[uk++];
        pos++;
        return TZpt;
    }else if (t[uk] == ';') {
        lex[i++] = t[uk++];
        pos++;
        return TTZpt;
    }
    lex[i++] = t[uk++];
    pos++;
    printf("%c", t[uk]);
    printError(EWrongChar);
    return TErr;
}

void Scanner::newLine() {
    line++;
    pos = 0;
}

void Scanner::setUK(int set_uk, int set_line, int set_pos) {
    uk = set_uk;
    line = set_line;
    pos = set_pos;
}

void Scanner::setUK(int i) {
    uk = i;
    line = tmpLine;
    pos = tmpPos;
}

int Scanner::getUK() {
    tmpLine = line;
    tmpPos = pos;
    return uk;
}

void Scanner::getUK(int &get_uk, int &get_line, int &get_pos) {
    get_uk = uk;
    get_line = line;
    get_pos = pos;
}

/*
#define TDataInt 1
#define TDataShort 2
#define TDataLong 3
#define TDataLongLong 4
typeConst - 10cc or 16cc
 */

int Scanner::getTypeConst(long long constanta, int typeConst) {
    if (INT32_MIN < constanta && constanta < INT32_MAX)
        return TDataInt;
    else
        return TDataLongLong;
}



