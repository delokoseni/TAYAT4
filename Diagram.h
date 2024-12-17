#pragma once

#include "Scaner.h"
#include "Tree.h"

class Diagram
{
private:
	Scaner* scaner;
	Tree* tree;
	void Description();						// Описание
	void DataMethod();							// Данные
	void Function();						// Функция
	void Type();							// Тип
	void List();							// Список
	void Variable(int typeData);			// Переменная
	void Assignment();						// Присваивание
	Data* Expression();						// Выражение
	void CompositeOperator();				// Составной оператор
	void OperatorsAndDescriptions();		// Операторы и описания
	void Operator();						// Оператор
	void FunctionCall();					// Вызов функции
	Data* Comparison();						// Сравнение
	Data* BitwiseShift();					// Побитовый сдвиг
	Data* Summand();						// Слагаемое
	Data* Multiplier();						// Множитель
	Data* UnaryOperation();					// Унарная операция
	Data* ElementaryExpression();			// Элементарное выражение
	void Cycle();							// Цикл
	void ReturnStatement();					// Оператор возврата (return)
	int LookForward(int pointer);			
	int Scan(type_lex lex);
	
public:
	Diagram(Scaner* scaner, Tree* tree);
	void Program();							// Программа

};