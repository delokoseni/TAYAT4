#include "Diagram.h"

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
		Data();
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
	int type, pointer;
	Variable();
	type = LookForward(1);
	while (type == typeComma) 
	{
		type = Scan(lex);
		Variable();
		type = LookForward(1);
	}
}

void Diagram::Data() 
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

	type = Scan(lex);
	if (type != typeId && type != typeMain)
	{
		scaner->PrintError("ожидался идентификатор, ", lex);
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

	type = Scan(lex);
	if (type != typeLeftBrace)
	{
		scaner->PrintError("ожидалась {, ", lex);
	}

	OperatorsAndDescriptions();

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
	type = Scan(lex);
	if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
	{
		scaner->PrintError("ожидался тип (int, short, long, float), ", lex);
	}
}

void Diagram::Variable() 
{
	type_lex lex;
	Node* newNode = new Node();
	int type = LookForward(1);

	if (type != typeId) 
	{
		type = Scan(lex);
		scaner->PrintError("ожидался идентификатор, ", lex);
	}

	int pointer = scaner->GetUK();
	type = Scan(lex);
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

	type = Scan(lex);
	if (type != typeEval)
	{
		scaner->PrintError("ожидалось =, ", lex);
	}

	Expression();
}

void Diagram::Expression() 
{
	type_lex lex;
	int type;

	Comparison();
	type = LookForward(1);
	while (type == typeEq || type == typeUnEq) 
	{
		type = Scan(lex);
		Comparison();
		type = LookForward(1);
	}
}

void Diagram::CompositeOperator() 
{
	type_lex lex;
	int type = Scan(lex);

	if (type != typeLeftBrace)
	{
		scaner->PrintError("ожидалась {, ", lex);
	}

	OperatorsAndDescriptions();

	type = Scan(lex);
	if (type != typeRightBrace)
	{
		scaner->PrintError("ожидалась }, ", lex);
	}
}

void Diagram::OperatorsAndDescriptions() 
{
	type_lex lex;
	int type = LookForward(1);

	while (type != typeRightBrace) 
	{
		if (type == typeInt || type == typeShort || type == typeLong || type == typeFloat) 
		{
			Data();
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
	if (type != typeSemicolon)
	{
		scaner->PrintError("ожидалась ;, ", lex);
	}
}

void Diagram::Comparison() 
{
	type_lex lex;
	BitwiseShift();
	int type = LookForward(1);
	while (type == typeLess || type == typeLessOrEq || type == typeMore || type == typeMoreOrEq) 
	{
		type = Scan(lex);
		BitwiseShift();
		type = LookForward(1);
	}
}

void Diagram::BitwiseShift()
{
	type_lex lex;
	int type;
	Summand();
	type = LookForward(1);
	while (type == typeBitwiseRight || type == typeBitwiseLeft) 
	{
		type = Scan(lex);
		Summand();
		type = LookForward(1);
	}
}

void Diagram::Summand() 
{
	type_lex lex;
	int type;
	Multiplier();
	type = LookForward(1);
	while (type == typePlus || type == typeMinus) 
	{
		type = Scan(lex);
		Multiplier();
		type = LookForward(1);
	}
}

void Diagram::Multiplier() 
{
	type_lex lex;
	int type;
	UnaryOperation();
	type = LookForward(1);
	while (type == typeMul || type == typeDiv || type == typeMod) 
	{
		type = Scan(lex);
		UnaryOperation();
		type = LookForward(1);
	}
}

void Diagram::UnaryOperation() 
{
	type_lex lex;
	int type = LookForward(1);

	if (type == typePlus || type == typeMinus)
	{
		type = Scan(lex);
		ElementaryExpression();
	}
	else
	{
		ElementaryExpression();
	}
}


void Diagram::ElementaryExpression() 
{
	type_lex lex;
	int type = LookForward(1);
	if (type == typeId) 
	{
		type = Scan(lex);
		return;
	}
	if (type == typeShort || type == typeFloat || type == typeInt || type == typeLong) 
	{
		type = Scan(lex);
		return;
	}
	if (type == typeLeftBracket) 
	{
		type = Scan(lex);
		Expression();
		type = Scan(lex);
		if (type != typeRightBracket)
		{
			scaner->PrintError("ожидалась ), ", lex);
		}
		return;
	}
	type = Scan(lex);
	scaner->PrintError("ожидалось выражение, ", lex);
}