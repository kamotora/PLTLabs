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

#define SIZE_MAX_LONGLONG_10 22

#define SIZE_MAX_LONGLONG_16 16
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


// ----------------------------------- Дельты -----------------------------------

// записать в дерево функцию.
// Создание доп.уровня для функции (в дополнение к будущему уровню блока)
#define DEL_SetFunc -101
// Записать переменную в дерево
#define DEL_SetVar -102

// установить флаг описания данных и запомнить тип в глобальной переменной dataType.
#define DEL_StartDecl -105

//  сбросить флаг описания данных
#define DEL_EndDecl -106

// добавить в дерево 2 пустые вершины (левую и правую) для блока
#define DEL_SetBlock -110

// выход из текущего уровня (конец блока)
#define DEL_EndBlock -111

// выход c уровня функции (конец блока + спец.вершин для ф-ии)
#define DEL_EndFunc -112

// найти в дереве функцию/переменную
#define DEL_FindFunc -120
#define DEL_FindVar -121

// проверка возвращаемого значения.
#define DEL_ReturnCheck -130

// приведение типов в присваивании.
#define DEL_MatchLeft -140

// приведение типов в выражении
#define DEL_Match -150
#define DEL_MatchCompare -151
// ++ и -- для констант - запрещено
#define DEL_CheckUnar -160

// тип константы
#define DEL_ConstType -170

// положить тип в магазин типов.
//#define DEL_PushType -180

// Вызов функции
#define DEL_CallFunc -190


#endif //COMPC___DEFS_H
