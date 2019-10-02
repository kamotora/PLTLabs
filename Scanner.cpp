#include "Scanner.h"
//
// Created by artem on 02.10.2019.
//

TypeLex keyWord[MAX_NUM_KEY_WORD] = {"for","int","long","short","return"};
int indexKeyWord[MAX_NUM_KEY_WORD] = {TFor,TInt,TLong,TShort,TReturn};

TScanner::TScanner(const char *fileName){
    getData(fileName);
    uk = 0;
    pos = 0;
    line = 1;
};

bool TScanner::isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

bool TScanner::isDigit10(char ch) {
    return ch >= '0' && ch <= '9';
}

bool TScanner::isDigit16(char ch) {
    return TScanner::isDigit10(ch) || ((ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'));
}

void TScanner::setUK(int i) {
    uk = i;
}

int TScanner::getUK() {
    return uk;
}

int TScanner::getPos() {
    return pos;
}

void TScanner::setPos(int _pos) {
    pos = _pos;
}
int TScanner::getLine() {
    return line;
}

void TScanner::setLine(int _line) {
    line = _line;
}
void TScanner::getData(const char * FileName) {
// ввод файла FileName, который содержит текст исходного модуля
    char aa;
    FILE * in = fopen(FileName,"r");
    if (in == nullptr){
        printError("Отсутствует входной файл");
        exit(1);
    }
    int i = 0;
    while(!feof(in)){
        fscanf(in,"%c",&aa);
        if (!feof(in))
            t[i++]=aa;
        if (i>=MAX_TEXT-1){
            printError("Слишком большой размер исходного модуля");
            break;
        }
    }
    // приписываем знак ’\0’ в конец текста
    t[i]='\0';
    fclose(in);
}

void TScanner::printError(const string& error) {
    cout << "Ошибка! " <<  error << "\n";
    exit(1);
}

void TScanner::printError(const string& error, TypeLex lex) {
    cout << "Ошибка! Строка " << line << ", позиция " << pos << ": " << error << " ( " << lex << " )\n";
    exit(1);
}

void TScanner::printWarning(int typeError) {
    printf("Предупреждение! Строка %d, позиция %d. ", line, pos);
    switch (typeError) {
        case WLongId :
            printf("Слишком длинный идентификатор. Его длина будет ограничена %d символами\n",MAX_LEX);
        break;
        default:
            printf("Неизвестная ошибка %d\n",typeError);
            break;
    }
    exit(1);
}

void TScanner::printError(int typeError) {
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

int TScanner::scanner(TypeLex lex)  {
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
        } else
            break;
    }

    if(t[uk] == '\0')
        return TEnd;

    if(isLetter(t[uk])){
        lex[i++] = t[uk++];
        pos++;
        while(isLetter(t[uk]) || isDigit10(t[uk])){
            lex[i++] = t[uk++];
            pos++;
            if(i == MAX_LEX){
                printWarning(ELongIntConst);
                break;
            }
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
                    if(i == MAX_LEN_INT16){
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
                if(i == MAX_LEN_INT10){
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
        if (t[uk] != '='){
            lex[i++] = t[uk++];
            pos++;
            return TGE;
        }
        else
            return TGT;

    } else if (t[uk] == '<') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] != '='){
            lex[i++] = t[uk++];
            pos++;
            return TLE;
        }
        else
            return TLT;

    } else if (t[uk] == '!') {
        lex[i++] = t[uk++];
        pos++;
        if (t[uk] != '='){
            lex[i++] = t[uk++];
            pos++;
            return TNEQ;
        }
        else {
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
    printError(EWrongChar);
    return TErr;
}

void TScanner::newLine() {
    line++;
    pos = 0;
}
