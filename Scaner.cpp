#define _CRT_SECURE_NO_WARNINGS

#include "Scaner.h"
#include <fstream>
#include <sstream>
#include <iostream>

type_lex keyword[maxKeyword] =
{
	"int", "short", "long", "float" "char", "while", "main"
};

int indexKeyword[maxKeyword] =
{
	typeInt, typeShort, typeLong, typeFloat, typeWhile, typeMain
};

void Scaner::PutUK(int uk)
{
	if(uk >= 0 && uk <= maxText)
		this->uk = uk;
}

int Scaner::GetUK()
{
    return uk;
}

void Scaner::PrintError(const char* error, const char* text)
{
	if (text[0] == '\0')
		std::cout << error << std::endl;
	else
		std::cout << error << " " << text << std::endl;
}

int Scaner::UseScaner(type_lex l)
{
    return 0;
}

void Scaner::GetData(const char* filename)
{
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();

		strncpy(text, buffer.str().c_str(), maxText - 1);
		text[maxText - 1] = '\0';

		std::cout << text << std::endl;
		std::cout << "_____________________________________________________________________________________________________	" << std::endl;
	}
	else
	{
		PrintError("Error opening file!", filename);
		return;
	}
}

Scaner::Scaner(const char* filename)
{
    GetData(filename);
    PutUK(0);
}
