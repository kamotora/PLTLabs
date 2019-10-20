//
// Created by artem on 02.10.2019.
//

#ifndef COMPC___DEFS_H
#define COMPC___DEFS_H

#include <iostream>
#include <cstring>

// Максимальная длина исходного модуля
#define MAX_TEXT 10000
// Максимальная длина лексемы
#define MAX_LEX 100
// Максимальная длина целой константы типа int,long
#define MAX_LEN_INT10 10
// Максимальная длина целой константы типа int,long
#define MAX_LEN_INT16 7
// Максимальное количество ключевых слов
#define MAX_NUM_KEY_WORD 5

//Ключевые слова
#define TFor 1
#define TReturn 2
#define TInt 3
#define TShort 4
#define TLong 5
#define TIdent 20

#define TConst10  30
#define TConst16  31

#define TZpt  40
#define TTZpt  41
#define TLeftRoundSkob  42
#define TRightRoundSkob  43
#define TLeftFigSkob  44
#define TRightFigSkob  45

//==
#define TEQ  60
//!=
#define TNEQ  61
//>
#define TGT  62
//>=
#define TGE  63
//<
#define TLT  64
//<=
#define TLE 65
#define TPlus 66
#define TMinus 67
#define TMul 68
#define TDiv 69
#define TMod 70
#define TSave 71
#define TAddSelf 72
#define TSubSelf 73

//Конец исходного модуля
#define TEnd 100
//Ошибочный символ
#define TErr 200


// -------------------------- Ошибки и предупреждения ---------------------------

// Типы ошибок
#define EWrongChar 1
#define EConst10StartFrom0 2
#define EWrongConst16 3
#define ELongIntConst 4

//Типы предупреждений
#define WLongId 20


typedef char TypeMod[MAX_TEXT];
typedef char TypeLex[MAX_LEX];


//Красный цвет для вывода в консоль
#define KRED  "\x1B[31m"
#endif //COMPC___DEFS_H
