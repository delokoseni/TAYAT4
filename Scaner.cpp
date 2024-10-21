#define _CRT_SECURE_NO_WARNINGS

#include "Scaner.h"
#include <fstream>
#include <sstream>
#include <iostream>

/**
* ������ ���������� �������� ���� � ���������
*/
type_lex keyword[maxKeyword] =
{
	"int", "short", "long", "float", "while", "main", "return"
};

/**
* ������ ���������������, ������� ������������� ���������� �������� ������ � ���������
*/
int indexKeyword[maxKeyword] =
{
	typeInt, typeShort, typeLong, typeFloat, typeWhile, typeMain, typeReturn
};

void Scaner::PutUK(int uk)
{
	if (uk >= 0 && uk <= maxText)
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

int Scaner::UseScaner(type_lex lex)
{
    int i = 0;
    lex[0] = '\0';

    while (true) 
    {
        // ���������� �������
        while (text[uk] == ' ' || text[uk] == '\t' || text[uk] == '\n') 
        {
            uk++;
        }

        // ����� ��������� 
        if (text[uk] == '\0') 
        {
            lex[i] = '\0';
            return typeEnd;
        }

        // ��������� ������������
        if (text[uk] == '/') 
        {
            uk++;
            if (text[uk] == '/') 
            {
                std::cout << "������ �����������." << std::endl;
                while (text[uk] != '\n' && text[uk] != '\0') 
                {
                    uk++;
                }
                continue;  
            }
            else 
            {
                // �������
                lex[i++] = '/';
                lex[i++] = '\0';
                return typeDiv;
            }
        }

        // ��������� �����
        if (isdigit(text[uk])) 
        {
            while (isdigit(text[uk]) && i < maxNumber - 1) 
            {
                lex[i++] = text[uk++];
            }

            // ��������� ������������ �����
            if (text[uk] == '.') {
                lex[i++] = text[uk++];
                while (isdigit(text[uk]) && i < maxNumber - 1) 
                {
                    lex[i++] = text[uk++];
                }
                lex[i] = '\0';
                if (i == maxNumber - 1 && isdigit(text[uk]))
                {
                    while (isdigit(text[uk])) 
                    {
                        uk++;
                    }
                    PrintError("��������� ��������� ������������ ����� �������: ", lex);
                    return typeError;
                }
                return typeFloat;
            }

            lex[i] = '\0';
            return typeInt;
        }

        // ��������� �����
        if (text[uk] == '.') 
        {
            lex[i++] = text[uk++];
            if (isdigit(text[uk])) 
            {
                while (isdigit(text[uk]) && i < maxNumber - 1) 
                {
                    lex[i++] = text[uk++];
                }
                lex[i] = '\0';
                if (i == maxNumber - 1 && isdigit(text[uk])) 
                {
                    while (isdigit(text[uk])) 
                    {
                        uk++;
                    }
                    PrintError("��������� ��������� ������������ ����� �������: ", lex);
                    return typeError;
                }
                return typeFloat;
            }
            else 
            {
                return typePoint;
            }
        }

        // ��������� ���������������
        if (isalpha(text[uk]) || text[uk] == '_') {
            while ((isalnum(text[uk]) || text[uk] == '_') && i < maxLex - 1) 
            {
                lex[i++] = text[uk++];
            }
            lex[i] = '\0';
            if (i == maxLex - 1 && (isalnum(text[uk]) || text[uk] == '_')) 
            {
                while (isalnum(text[uk]) || text[uk] == '_') 
                {
                    uk++;
                }
                PrintError("������������� ��������� ������������ ����� �������.", lex);
                return typeError;
            }

            // ���������, �������� �� ������������� �������� ������
            for (int j = 0; j < maxKeyword; j++) 
            {
                if (strcmp(lex, keyword[j]) == 0) 
                {
                    return indexKeyword[j];
                }
            }
            return typeId;
        }

        // ��������� ����������� ��������
        switch (text[uk]) 
        {
        case ',':
            uk++; lex[i++] = ','; lex[i] = '\0'; return typeComma;
        case ';':
            uk++; lex[i++] = ';'; lex[i] = '\0'; return typeSemicolon;
        case '(':
            uk++; lex[i++] = '('; lex[i] = '\0'; return typeLeftBracket;
        case ')':
            uk++; lex[i++] = ')'; lex[i] = '\0'; return typeRightBracket;
        case '{':
            uk++; lex[i++] = '{'; lex[i] = '\0'; return typeLeftBrace;
        case '}':
            uk++; lex[i++] = '}'; lex[i] = '\0'; return typeRightBrace;
        case '+':
            uk++; lex[i++] = '+'; lex[i] = '\0'; return typePlus;
        case '-':
            uk++; lex[i++] = '-'; lex[i] = '\0'; return typeMinus;
        case '*':
            uk++; lex[i++] = '*'; lex[i] = '\0'; return typeMul;
        case '%':
            uk++; lex[i++] = '%'; lex[i] = '\0'; return typeMod;
        case '=':
            uk++;
            lex[i++] = '=';
            if (text[uk] == '=') 
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeEq;
            }
            else 
            {
                lex[i] = '\0';
                return typeEval;
            }
        case '!':
            uk++;
            lex[i++] = '!';
            if (text[uk] == '=') 
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeUnEq;
            }
            else 
            {
                lex[i] = '\0';
                PrintError("����������� ������: ", lex);
                return typeError;
            }
        case '>':
            uk++;
            lex[i++] = '>';
            if (text[uk] == '=') 
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeMoreOrEq;
            }
            else if (text[uk] == '>') 
            {
                uk++;
                lex[i++] = '>';
                lex[i] = '\0';
                return typeBitwiseRight;
            }
            else {
                lex[i] = '\0';
                return typeMore;
            }
        case '<':
            uk++;
            lex[i++] = '<';
            if (text[uk] == '=') 
            {
                uk++;
                lex[i++] = '=';
                lex[i] = '\0';
                return typeLessOrEq;
            }
            else if (text[uk] == '<') 
            {
                uk++;
                lex[i++] = '<';
                lex[i] = '\0';
                return typeBitwiseLeft;
            }
            else 
            {
                lex[i] = '\0';
                return typeLess;
            }
        default:
            lex[i++] = text[uk++];
            lex[i] = '\0';
            PrintError("����������� ������ � ������ ", lex);
            return typeError;
        }
    }
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
		std::cout << std::endl << "��������� ������ �������:" << std::endl;
	}
	else
	{
		PrintError("������ �������� �����.", filename);
		return;
	}
}

Scaner::Scaner(const char* filename)
{
	GetData(filename);
	PutUK(0);
}
