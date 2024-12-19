﻿#include "Diagram.h"

Diagram::Diagram(Scaner* scaner, Tree* tree)
{
	this->scaner = scaner;
	this->tree = tree;
}

int Diagram::LookForward(int pos) 
{
	type_lex lex;
	int saved_pointer = scaner->GetUK();
	int next_type;
	for (int i = 0; i < pos; i++)
		next_type = scaner->UseScaner(lex);
	scaner->PutUK(saved_pointer);
	return next_type;
}

int Diagram::Scan(type_lex lex) 
{
	return scaner->UseScaner(lex);
}

void Diagram::Program() 
{
	type_lex lex;
	int type;
	type = LookForward(1);
	while (type == typeInt || type == typeShort || type == typeLong || type == typeFloat) 
	{
		Description();
		type = LookForward(1);
	}
	if (type != typeEnd) 
	{
		type = Scan(lex);
		scaner->PrintError("ожидался конец, ", lex);
	}
}

void Diagram::Description() 
{
	type_lex lex;
	int type = LookForward(1);
	int simbol = LookForward(3);
	if ((type == typeInt || type == typeShort || type == typeLong || type == typeFloat) && simbol != typeLeftBracket) 
	{
		DataMethod();
		return;
	}
	if ((type == typeInt || type == typeShort || type == typeLong || type == typeFloat) && simbol == typeLeftBracket) 
	{
		Function();
		return;
	}
	type = Scan(lex);
	scaner->PrintError("ожидался тип (int, short, long, float), ", lex);
}

void Diagram::List() 
{
	type_lex lex;
	type_lex* lexData;
	int type, pointer;
	int typeData = LookForward(1);
	Scan(lex);
	Variable(typeData);
	type = LookForward(1);
	while (type == typeComma) 
	{
		type = Scan(lex);
		Variable(typeData);
		type = LookForward(1);
	}
}

void Diagram::DataMethod() 
{
	type_lex lex;
	int type_;
	Type();
	List();
	type_ = Scan(lex);
	if (type_ != typeSemicolon)
	{
		scaner->PrintError("ожидалась ;, ", lex);
	}
}

void Diagram::Function() 
{
	type_lex lex;
	int type = Scan(lex);
	if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
	{
		scaner->PrintError("ожидался тип (int, short, long, float), ", lex);
	}

	int type1 = type;

	type = Scan(lex);
	if (type != typeId && type != typeMain)
	{
		scaner->PrintError("ожидался идентификатор, ", lex);
	}

	if (tree->IsDoublicateId(tree, lex)) {
		scaner->PrintError("Переопределение", lex);
	}

	// Создаём новый узел для функции
	Node* newNode = new Node();
	newNode->id = lex;  // Назначаем идентификатор
	newNode->objectType = OBJ_FUNC;
	newNode->data.DataType = tree->GetDataType(type1);

	// Вставляем узел в дерево
	tree->SetLeft(newNode);
	tree = tree->GetLeft(); // Переход к новому узлу
	tree->SetRight(NULL);

	Tree* tmpTree = tree; // Сохраняем текущий указатель дерева
	tree = tree->GetRight(); // Переход к правому поддереву

	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("ожидалась (, ", lex);
	}

	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scaner->PrintError("ожидалась ), ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBrace)
	{
		scaner->PrintError("ожидалась {, ", lex);
	}

	OperatorsAndDescriptions();

	// Возвращаемся к предыдущему узлу
	tree = tmpTree;

	type = Scan(lex);
	if (type != typeRightBrace)
	{
		scaner->PrintError("ожилалась }, ", lex);
	}
}

void Diagram::Type() 
{
	type_lex lex;
	int type;
	type = LookForward(1);
	if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
	{
		scaner->PrintError("ожидался тип (int, short, long, float), ", lex);
	}
}

void Diagram::Variable(int typeData1) 
{
	type_lex lex;
	Node* newNode = new Node();
	int type;
	if (typeData1 != typeInt && typeData1 != typeShort && typeData1 != typeLong && typeData1 != typeFloat)
	{
		scaner->PrintError("ожидался тип (int, short, long, float), ", lex);
	}
	if (typeData1 == typeInt)
		newNode->data.DataType = TYPE_INTEGER;
	else if (typeData1 == typeShort)
		newNode->data.DataType = TYPE_SHORT;
	else if (typeData1 == typeLong)
		newNode->data.DataType = TYPE_LONG;
	else if (typeData1 == typeFloat)
		newNode->data.DataType = TYPE_FLOAT;
	else
		newNode->data.DataType = TYPE_UNKNOWN;
	type = LookForward(1);
	type_data typeData = tree->GetDataType(type);

	if (type != typeId) 
	{
		type = Scan(lex);
		scaner->PrintError("ожидался идентификатор, ", lex);
	}

	int pointer = scaner->GetUK();
	type = Scan(lex);

	if (tree->IsDoublicateId(tree, lex)) {
		tree->PrintError("Переопределение", lex);
	}

	newNode->id = lex;  // Устанавливаем идентификатор
	newNode->objectType = OBJ_VAR;

	type = LookForward(1);
	if (type == typeEval) {
		newNode->flagInit = 1;
	}
	else
	{
		newNode->flagInit = 0;
	}

	// Добавляем узел в левое поддерево
	tree->SetLeft(newNode);

	// Переход к левому дочернему узлу для дальнейших операций
	tree = tree->GetLeft();

	scaner->PutUK(pointer);

	type = LookForward(2);
	if (type == typeEval) 
	{
		Assignment();
		return;
	}
	type = Scan(lex);
}

void Diagram::Assignment() 
{
	type_lex lex;
	int type = Scan(lex);

	if (type != typeId) 
	{
		scaner->PrintError("ожидался идентификатор, ", lex);
	}

	Tree* node = tree->FindUp(lex);

	if (node == NULL) {
		scaner->PrintError("Семантическая ошибка. ID не найден", lex);
	}

	if (node->GetSelfObjectType() != OBJ_VAR ) {
		scaner->PrintError("Семантическая ошибка. Попытка использования не переменной в присваивании", lex);
	}

	node->SetInit();

	// Получаем тип переменной узла
	type_data varType = node->GetSelfDataType();
	type = Scan(lex);
	if (type != typeEval)
	{
		scaner->PrintError("ожидалось =, ", lex);
	}

	//Expression();
	Data* val = Expression();
	node->SetValue(node->GetSelfId(), val->Value);
}

Data* Diagram::Expression() 
{
	type_lex lex;
	int type;
	Data* result = new Data();

	result = Comparison();
	type = LookForward(1);
	while (type == typeEq || type == typeUnEq) 
	{
		type = Scan(lex);
		//Comparison();
		if (type == typeEq) 
			result->Value.Float = (result->Value.Float == Comparison()->Value.Float);
		if (type == typeLessOrEq) //???
			result->Value.Float = !(result->Value.Float == Comparison()->Value.Float);
		type = LookForward(1);

	}

	return result;
}

void Diagram::CompositeOperator() 
{
	type_lex lex;
	int type = Scan(lex);
	Tree* varNode = NULL;
	type_data typeData = tree->GetDataType(type);

	if (type != typeLeftBrace)
	{
		scaner->PrintError("ожидалась {, ", lex);
	}

	Node* newNode = new Node();
	newNode->id = lex;
	newNode->objectType = OBJ_FUNC;
	newNode->data.DataType = typeData;
	if (varNode != NULL) newNode->pointer = varNode;
	tree->SetLeft(newNode);
	tree = tree->GetLeft();
	tree->SetRight(NULL);
	Tree* tmpTree = tree;
	tree = tree->GetRight();

	OperatorsAndDescriptions();

	type = Scan(lex);
	if (type != typeRightBrace)
	{
		scaner->PrintError("ожидалась }, ", lex);
	}
	tree = tmpTree;
}

void Diagram::OperatorsAndDescriptions() 
{
	type_lex lex;
	int type = LookForward(1);

	while (type != typeRightBrace) 
	{
		if (type == typeInt || type == typeShort || type == typeLong || type == typeFloat) 
		{
			DataMethod();
		}
		else Operator();
		type = LookForward(1);
	}
}

void Diagram::Operator() 
{
	type_lex lex;
	int type = LookForward(1);

	if (type == typeReturn) 
	{
		ReturnStatement();
		return;
	}

	if (type == typeSemicolon) 
	{
		type = Scan(lex);
		return;
	}

	if (type == typeLeftBrace) 
	{
		CompositeOperator();
		return;
	}

	if (type == typeWhile)
	{
		Cycle();
		return;
	}

	int type2 = LookForward(2);
	if (type == typeId && type2 == typeLeftBracket) 
	{
		FunctionCall();
		type = Scan(lex);
		if (type != typeSemicolon)
			scaner->PrintError("ожидалась ;, ", lex);
		
		return;
	}

	if (type == typeId && type2 == typeEval) 
	{
		Assignment();
		type = Scan(lex);
		if (type != typeSemicolon)
			scaner->PrintError("ожидалась ;, ", lex);
		return;
	}

	if (type == typeId) 
	{
		Expression();
		return;
	}

	type = Scan(lex);
	scaner->PrintError("ожидался оператор, ", lex);
}

void Diagram::ReturnStatement() 
{
	type_lex lex;
	int type = Scan(lex);

	if (type != typeReturn) 
	{
		scaner->PrintError("ожидалось return, ", lex);
	}

	Expression();

	type = Scan(lex);
	if (type != typeSemicolon) 
	{
		scaner->PrintError("ожидалась ; после return <выражение>, ", lex);
	}
}

void Diagram::Cycle()
{
	type_lex lex;
	int type = Scan(lex);

	if (type != typeWhile) 
	{
		scaner->PrintError("ожидалось while, ", lex);
	}

	type = Scan(lex);
	if (type != typeLeftBracket) 
	{
		scaner->PrintError("ожидалась (, ", lex);
	}

	Expression();

	type = Scan(lex);
	if (type != typeRightBracket) 
	{
		scaner->PrintError("ожидалась ), ", lex);
	}

	Operator();
}

void Diagram::FunctionCall() 
{
	type_lex lex;
	int type = Scan(lex);

	if (type != typeId)
	{
		scaner->PrintError("ожидался идентификатор, ", lex);
	}

	// Ищем узел, называющийся объектом
	Tree* objectNode = tree->FindUp(lex);
	// Получаем указатель на функцию из функции с тем же именем в родительском узле
	Tree* methodNode = objectNode->FindFunction(lex); // Функция для поиска по имени функции в родительском узле на findUp
	if (methodNode == NULL) {
		scaner->PrintError("Функция не найдена", lex);
		return; // Выход из функции при ошибке
	}

	// Проверяем, что узел является функцией
	if (methodNode->GetSelfObjectType() != OBJ_FUNC) {
		scaner->PrintError("Не является функцией", lex);
	}


	type = Scan(lex);
	if (type != typeLeftBracket)
	{
		scaner->PrintError("ожидалась (, ", lex);
	}

	type = Scan(lex);
	if (type != typeRightBracket)
	{
		scaner->PrintError("ожидалась ), ", lex);
	}


}

Data* Diagram::Comparison()
{
	Data* result = new Data();
	type_lex lex;
	result = BitwiseShift();
	int type = LookForward(1);
	while (type == typeLess || type == typeLessOrEq || type == typeMore || type == typeMoreOrEq) 
	{
		type = Scan(lex);
		Tree* node = tree->FindUp(lex);
		//BitwiseShift();
		result = BitwiseShift();
		type = LookForward(1);
	}
	return result;
}

Data* Diagram::BitwiseShift()
{
	Data* result = new Data();
	type_lex lex;
	int type;
	result = Summand();
	type = LookForward(1);
	while (type == typeBitwiseRight || type == typeBitwiseLeft) 
	{
		if (result->DataType == TYPE_FLOAT)
			scaner->PrintError("Недопустимый тип данных для побитового сдвига.", lex);
		type = Scan(lex);
		if (type == typeBitwiseRight)
			result->Value.Float = (int)result->Value.Float >> (int)Summand()->Value.Float; //Исправить
		if (type == typeBitwiseLeft)
			result->Value.Float = (int)result->Value.Float << (int)Summand()->Value.Float; //Исправить
		type = LookForward(1);
	}
	return result;
}

Data* Diagram::Summand() 
{
	Data* result = new Data();
	type_lex lex;
	int type;
	result = Multiplier();
	type = LookForward(1);
	while (type == typePlus || type == typeMinus) 
	{
		type = Scan(lex);
		//Multiplier();
		if (type == typePlus)
			result->Value.Float += Multiplier()->Value.Float;
		if (type == typeMinus)
			result->Value.Float -= Multiplier()->Value.Float;
		type = LookForward(1);
	}
	return result;
}

Data* Diagram::Multiplier() 
{
	Data* result = new Data();
	type_lex lex;
	int type;
	result = UnaryOperation();
	type = LookForward(1);
	while (type == typeMul || type == typeDiv || type == typeMod) 
	{
		type = Scan(lex);
		//Tree* node = tree->FindUp(lex);
		//UnaryOperation();
		if (type == typeMul) {
			Data* buffer = UnaryOperation();
			result->DataType = buffer->DataType;
			result->Value.Float *= buffer->Value.Float;
		}
		if (type == typeDiv) {
			Data* buffer = UnaryOperation();
			if (buffer->DataType != TYPE_FLOAT && result->DataType != TYPE_FLOAT && result->Value.Float != 0) {
				result->Value.Float = (int)(result->Value.Float / buffer->Value.Float);
			}
			else
				if (buffer->Value.Float != 0)
					result->Value.Float /= buffer->Value.Float;
				else
					scaner->PrintError("Деление на ноль.", lex);
		}
		if (type == typeMod) {
			Data* buffer = ElementaryExpression(); //???
			result->DataType = buffer->DataType;
			result->Value.Float = fmod(result->Value.Float, buffer->Value.Float);
		}
		type = LookForward(1);
	}
	return result;
}

Data* Diagram::UnaryOperation() //Продолжить
{
	Data* result = new Data();
	type_lex lex;
	int type = LookForward(1);

	/*if (type == typePlus || type == typeMinus)
	{
		type = Scan(lex);
		ElementaryExpression();
	}
	else
	{
		ElementaryExpression();
	}*/
	if (type == typePlus) {
		type = Scan(lex);
		Data* buffer = ElementaryExpression();
		result->DataType = buffer->DataType;
		result->Value.Float += buffer->Value.Float;
	}
	if (type == typeMinus) {
		type = Scan(lex);
		Data* buffer = ElementaryExpression();
		result->DataType = buffer->DataType;
		result->Value.Float -= buffer->Value.Float;
	}
	result = ElementaryExpression();
	return result;
}



Data* Diagram::ElementaryExpression() 
{
	Data* result = new Data();
	type_lex lex;
	int type = LookForward(1);
	if (type == typeInt || type == typeFloat || type == typeShort || type == typeLong) {
		type = Scan(lex);
		switch (type) {
		case typeInt:

			result->Value.Float = std::stod(std::string(lex));
			result->DataType = TYPE_INTEGER;
			return result;
			break;
		case typeShort:

			result->Value.Float = std::stod(std::string(lex));
			result->DataType = TYPE_SHORT;
			return result;
			break;
		case typeLong:

			result->Value.Float = std::stod(std::string(lex));
			result->DataType = TYPE_LONG;
			return result;
			break;
		case typeFloat:
			try {
				result->Value.Float = std::stod(lex);
				result->DataType = TYPE_FLOAT;
			}
			catch (const std::invalid_argument&) {
				scaner->PrintError("Недопустимое значение для преобразования целых чисел.", lex);
			}
			catch (const std::out_of_range&) {
				scaner->PrintError("Целочисленное значение выходит за пределы допустимого диапазона.", lex);
			}
			return result;
			break;
		}
	}
	if (type == typeId) 
	{
		if (LookForward(2) == typeLeftBracket) {
			FunctionCall();
			return result;
		}
		type = Scan(lex);
		Tree* node = tree->FindUp(lex);
		if (node == nullptr)
		{
			scaner->PrintError("Семантическая ошибка. Переменная не найдена", lex);
		}

		if(node != NULL)
			if (node->IsSelfInit() == 0)
			{
				scaner->PrintError("Семантическая ошибка. Переменная не инициализирована", lex);
		}
		result = node->GetData(); //???
		return result;
	}
	if (type == typeShort || type == typeFloat || type == typeInt || type == typeLong) 
	{
		type = Scan(lex);
		return result;
	}
	if (type == typeLeftBracket) 
	{
		type = Scan(lex);
		result = Expression();
		type = Scan(lex);
		if (type != typeRightBracket)
			scaner->PrintError("ожидалась ), ", lex);
		return result;
	}
	type = Scan(lex);
	scaner->PrintError("ожидалось выражение, ", lex);
	return result;
}