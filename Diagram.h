#pragma once

#include "Scaner.h"

class Diagram
{
private:
	//type_data last_type_data;
	//type_object last_type_object;
	Scaner* scaner;
	void description();                  // Описание
	void data();                         // Данные
	void function(int type);             // Функция
	void type();                         // Тип
	void list();                         // Список
	void variable();                     // Переменная
	void assignment();                   // Присваивание
	void expression();                   // Выражение
	void composite_operator();           // Составной оператор
	void operators_and_descriptions();   // Операторы и описания
	void operator_();                    // Оператор
	void function_call();                // Вызов функции
	void comparison();                   // Сравнение
	void addendum();                     // Добавочное
	void multiplier();                   // Умножитель
	void unary_operation();              // Унарная операция
	void elementary_expression();        // Элементарное выражение
	int look_forward(int pointer);
	int scan(type_lex lex);
	void element();
	void return_statement();
public:
	//Tree* root;
	Diagram(Scaner* scaner) 
	{
		this->scaner = scaner;
		//this->root = new Tree(scaner);
		//this->root->set_current(this->root);
	}
	void program();						// Программа
};