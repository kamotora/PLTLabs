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
// Максимальный размер магазина
#define MAX_MAG 1000

// Максимальное количество ключевых слов
#define MAX_NUM_KEY_WORD 5
const char MAX_SHORT_10[] = {'3', '2', '7', '6', '7', '\0'};
const char MAX_SHORT_16[] = {'f', 'f', '\0'};

const char MAX_INT_10[] = {"2147483647\0"};
const char MAX_INT_16[] = {'f', 'f', 'f', 'f', '\0'};

const char MAX_LONGLONG_10[] = {"9223372036854775807\0"};
const char MAX_LONGLONG_16[] = {'f', 'f', 'f', 'f', 'f', 'f', 'f', 'f', '\0'};
//Ключевые слова
#define TFor 1
#define TReturn 2
#define TInt 3
#define TShort 4
#define TLong 5
#define TLongLong 6
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
#define TEnd 90
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
#define WPrivedenie 21
#define WDifferentTypesFunc 22
#define WSmallType 23
#define WUndefined 24

// ---------------------------- Типы узлов в дереве -----------------------------

#define TNodeEmpty 0
#define TNodeVar 1
#define TNodeFunction 2
#define TNodeConst 3

const char *TNodeToName(int TNode);

// -------------------------------- Типы данных ---------------------------------
#define TDataUndefined 0
#define TDataShort 1
#define TDataInt 2
#define TDataLong 3
#define TDataLongLong 4

std::string TDataToName(int TData);

typedef char TypeMod[MAX_TEXT];
typedef char TypeLex[MAX_LEX];

// -------------------------------- Нетерминалы ---------------------------------

#define netermProgram 100
#define netermDescription 101
#define netermData 102
#define netermType 103
#define netermType2 104
#define netermType3 105
#define netermList 114
#define netermList2 115
#define netermAssign 116
#define netermAssign2 117
#define netermSostOper 118
#define netermBlockSostOper 132
#define netermOper 119
#define netermExpr1 120
#define netermExpr11 121
#define netermExpr2 122
#define netermExpr21 123
#define netermExpr3 124
#define netermExpr31 125
#define netermExpr4 126
#define netermExpr41 127
#define netermExpr5 128
#define netermExpr51 129
#define netermExpr6 130
#define netermFuncCallOrVar 131


#endif //COMPC___DEFS_H
