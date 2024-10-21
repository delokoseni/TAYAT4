#pragma once
#include "Defines.h"

class Scaner
{

private:
	type_mod text; // �������� �����
	int uk;		   // ��������� ������� ������� � �������� ������

public:
	void PutUK(int uk);				// ���������� ��������� ������� ������� � �������� ������
	int GetUK();					// �������� ��������� ������� ������� � �������� ������
	void PrintError(const char* error, const char* text);	// ����� ������
	int UseScaner(type_lex lex);							// ������ ������ �������
	void GetData(const char* filename);						// ��������� ���������� �� �����
	Scaner(const char* filename);

};

