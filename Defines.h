#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxText 100000			// Максимальная длина текста
#define maxLex 100				// Максимальная длина лексемы
#define maxKeyword 16			// Максимальная длина ключевого слова
typedef char type_mod[maxText]; // Текст
typedef char type_lex[maxLex];  // Лексема

/**
* Тип лексем
*/
#define typeId 1

/**
* Ключевые слова
*/
#define typeShort 10
#define typeLong 11
#define typeInt 12
#define typeFloat 13
#define typeWhile 14
#define typeReturn 15
#define typeMain 16

/**
* Константы
*/
#define constInt 20
#define constFloat 21

/**
* Специальные знаки
*/
#define typePoint 30			// .
#define typeComma 31			// ,
#define typeSemicolon 32		// ;
#define typeLeftBracket 33		// (
#define typeRightBracket 34		// )
#define typeLeftBrace 35		// {
#define typeRightBrace 36		// }

/**
* Знаки операций
*/
#define typeEval 40				// =
#define typeUnEq 41				// !=
#define typeEq 42				// ==
#define typeMore 43				// >
#define typeMoreOrEq 44			// >=
#define typeLess 45				// <
#define typeLessOrEq 46			// <=
#define typeBitwiseRight 47		// >>
#define typeBitwiseLeft 48		// <<
#define typeMul 49				// *
#define typeDiv 50				// /
#define typeMod 51				// %
#define typePlus 52				// +
#define typeMinus 53			// -

/**
* Дополнительно
*/
#define typeEnd 100
#define typeError 404