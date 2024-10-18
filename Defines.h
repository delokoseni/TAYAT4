#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxText 100000			// ������������ ����� ������
#define maxLex 100				// ������������ ����� �������
#define maxKeyword 16			// ������������ ����� ��������� �����
typedef char type_mod[maxText]; // �����
typedef char type_lex[maxLex];  // �������

/**
* ��� ������
*/
#define typeId 1

/**
* �������� �����
*/
#define typeShort 10
#define typeLong 11
#define typeInt 12
#define typeFloat 13
#define typeWhile 14
#define typeReturn 15
#define typeMain 16

/**
* ���������
*/
#define constInt 20
#define constFloat 21

/**
* ����������� �����
*/
#define typePoint 30			// .
#define typeComma 31			// ,
#define typeSemicolon 32		// ;
#define typeLeftBracket 33		// (
#define typeRightBracket 34		// )
#define typeLeftBrace 35		// {
#define typeRightBrace 36		// }

/**
* ����� ��������
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
* �������������
*/
#define typeEnd 100
#define typeError 404