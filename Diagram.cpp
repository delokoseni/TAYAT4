#include "Diagram.h"

Diagram::Diagram(Scaner* scaner)
{
	this->scaner = scaner;
}

int Diagram::look_forward(int pos) {
	type_lex lex;
	int saved_pointer = scaner->GetUK();
	int next_type;
	for (int i = 0; i < pos; i++)
		next_type = scaner->UseScaner(lex);
	scaner->PutUK(saved_pointer);
	return next_type;
}

int Diagram::scan(type_lex lex) {
	return scaner->UseScaner(lex);
}

void Diagram::program() {
	type_lex lex;
	int type;
	type = look_forward(1);
	while (type == typeInt || type == typeShort || type == typeLong || type == typeFloat) {
		description();
		type = look_forward(1);
	}
	if (type != typeEnd) {
		type = scan(lex);
		scaner->PrintError("Expected end got", lex);
	}
}

void Diagram::description() {
	type_lex lex;
	int type = look_forward(1);
	int simbol = look_forward(3);
	if ((type == typeInt || type == typeShort || type == typeLong || type == typeFloat) && simbol != typeLeftBracket) {
		data();
		return;
	}
	if ((type == typeInt || type == typeShort || type == typeLong || type == typeFloat) && simbol == typeLeftBracket) {
		function();
		return;
	}
	type = scan(lex);
	scaner->PrintError("Expected type got", lex);
}

void Diagram::list() {
	type_lex lex;
	int type, pointer;

	element();

	type = look_forward(1);

	while (type == typeComma) {
		type = scan(lex);
		element();
		type = look_forward(1);
	}
}

void Diagram::element() {

	type_lex lex;
	int type;
	type = look_forward(1);
	if (type == typeId) {
		variable();
		return;
	}
	else {
		type = scaner->UseScaner(lex);
		scaner->PrintError("Expected element got", lex);
	}
}

void Diagram::data() {
	type_lex lex;
	int type_;

	type();

	list();

	type_ = scan(lex);
	if (type_ != typeSemicolon)
		scaner->PrintError("Expected ; got", lex);
}

void Diagram::function() {
	type_lex lex;
	int type = scan(lex);
	if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
		scaner->PrintError("Expected type got", lex);
	type = scan(lex);
	if (type != typeId && type != typeMain)
		scaner->PrintError("Expected identificator got", lex);

	type = scan(lex);
	if (type != typeLeftBracket)
		scaner->PrintError("Expected ( got", lex);

	type = scan(lex);
	if (type != typeRightBracket)
		scaner->PrintError("Expected ) got", lex);

	type = scan(lex);
	if (type != typeLeftBrace)
		scaner->PrintError("Expected { got", lex);

	operators_and_descriptions();

	type = scan(lex);
	if (type != typeRightBrace)
		scaner->PrintError("Expected } got", lex);
}

void Diagram::type() {
	type_lex lex;
	int type;
	type = scan(lex);
	if (type != typeInt && type != typeShort && type != typeLong && type != typeFloat)
		scaner->PrintError("Expected type (int, short, long, float) got", lex);
}

void Diagram::variable() {
	type_lex lex;
	int type;

	type = look_forward(1);

	if (type != typeId) {
		type = scan(lex);
		scaner->PrintError("Expected identificator got", lex);
	}

	int pointer = scaner->GetUK();
	type = scan(lex);
	scaner->PutUK(pointer);

	type = look_forward(2);
	if (type == typeEval) {
		assignment();
		return;
	}
	type = scan(lex);
}

void Diagram::assignment() {
	type_lex lex;
	int type;

	type = scan(lex);
	if (type != typeId) {
		scaner->PrintError("Expected identificator got", lex);
	}

	type = scan(lex);
	if (type != typeEval)
		scaner->PrintError("Expected = got", lex);

	expression();
}

void Diagram::expression() {
	type_lex lex;
	int type;

	comparison();
	type = look_forward(1);
	while (type == typeEq || type == typeUnEq) {
		type = scan(lex);
		comparison();
		type = look_forward(1);
	}
}

void Diagram::composite_operator() {
	type_lex lex;
	int type;

	type = scan(lex);
	if (type != typeLeftBrace)
		scaner->PrintError("Expected { got", lex);

	operators_and_descriptions();

	type = scan(lex);
	if (type != typeRightBrace)
		scaner->PrintError("Expected } got", lex);

}

void Diagram::operators_and_descriptions() {
	type_lex lex;
	int type;

	type = look_forward(1);
	while (type != typeRightBrace) {
		if (type == typeInt || type == typeShort || type == typeLong || type == typeFloat) {
			data();
		}
		else operator_();
		type = look_forward(1);

	}
}

void Diagram::operator_() {
	type_lex lex;
	int type;

	type = look_forward(1);

	if (type == typeReturn) {
		return_statement();
		return;
	}

	if (type == typeSemicolon) {
		type = scan(lex);
		return;
	}

	if (type == typeLeftBrace) {
		composite_operator();
		return;
	}

	if (type == typeWhile)
	{
		cycle();
		return;
	}

	int type2 = look_forward(2);
	if (type == typeId && type2 == typeLeftBracket) {
		function_call();
		return;
	}

	if (type == typeId && type2 == typeEval) {
		assignment();
		type = scan(lex);
		if (type != typeSemicolon)
			scaner->PrintError("Expected ; got", lex);
		return;
	}

	type = scan(lex);
	scaner->PrintError("Expected operator got", lex);
}

void Diagram::return_statement() {
	type_lex lex;
	int type;

	type = scan(lex);
	if (type != typeReturn) {
		scaner->PrintError("Expected return got", lex);
	}

	expression();

	type = scan(lex);
	if (type != typeSemicolon) {
		scaner->PrintError("Expected ; after return statement got", lex);
	}
}

void Diagram::cycle()
{
	type_lex lex;
	int type;

	type = scan(lex);
	if (type != typeWhile) {
		scaner->PrintError("Expected while got", lex);
	}

	type = scan(lex);
	if (type != typeLeftBracket) {
		scaner->PrintError("Expected ( got", lex);
	}

	expression();

	type = scan(lex);
	if (type != typeRightBracket) {
		scaner->PrintError("Expected ) got", lex);
	}

	operator_();
}

void Diagram::function_call() {
	type_lex lex;
	int type;

	type = scan(lex);
	if (type != typeId)
		scaner->PrintError("Expected identificator got", lex);

	type = scan(lex);
	if (type != typeLeftBracket)
		scaner->PrintError("Expected ( got", lex);

	type = scan(lex);
	if (type != typeRightBracket)
		scaner->PrintError("Expected ) got", lex);

	type = scan(lex);
	if (type != typeSemicolon)
		scaner->PrintError("Expected ; got", lex);	
}

void Diagram::comparison() {
	type_lex lex;
	int type;
	bitwiseshift();
	type = look_forward(1);
	while (type == typeLess || type == typeLessOrEq || type == typeMore || type == typeMoreOrEq) {
		type = scan(lex);
		bitwiseshift();
		type = look_forward(1);
	}
}

void Diagram::bitwiseshift()
{
	type_lex lex;
	int type;

	addendum();

	type = look_forward(1);
	while (type == typeBitwiseRight || type == typeBitwiseLeft) {
		type = scan(lex);
		addendum();
		type = look_forward(1);
	}
}

void Diagram::addendum() {
	type_lex lex;
	int type;

	multiplier();

	type = look_forward(1);
	while (type == typePlus || type == typeMinus) {
		type = scan(lex);
		multiplier();
		type = look_forward(1);
	}
}

void Diagram::multiplier() {
	type_lex lex;
	int type;

	unary_operation();

	type = look_forward(1);
	while (type == typeMul || type == typeDiv || type == typeMod) {
		type = scan(lex);
		unary_operation();
		type = look_forward(1);
	}
}

void Diagram::unary_operation() {
	type_lex lex;
	int type = look_forward(1);

	if (type == typePlus || type == typeMinus)
	{
		type = scan(lex);
		elementary_expression();
	}
	else
		elementary_expression();
}


void Diagram::elementary_expression() {
	type_lex lex;
	int type = look_forward(1);
	if (type == typeId) {
		type = scan(lex);
		int type = look_forward(1);
		return;
	}
	else if (type == typeShort || type == typeFloat || type == typeInt || type == typeLong) {
		type = scan(lex);
		return;
	}
	else if (type == typeLeftBracket) {
		type = scan(lex);
		expression();
		type = scan(lex);
		if (type != typeRightBracket)
			scaner->PrintError("Expected ) got ", lex);
		return;
	}
	else {
		type = scan(lex);
		scaner->PrintError("Expected expression got", lex);
	}
}