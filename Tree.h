#pragma once

#include "Scaner.h"

enum type_data 
{
	TYPE_UNKNOWN = 0,
	TYPE_SHORT = 1,
	TYPE_INTEGER = 2,
	TYPE_LONG = 3,
	TYPE_FLOAT = 4,
};

enum type_object 
{
	OBJ_VAR = 1,
	OBJ_CONST = 2,
	OBJ_FUNC = 3,
};

class Tree;

struct Node 
{
	std::string id;
	type_object objectType;
	type_data dataType;
	int flagInit;
	Tree* pointer; // Указатель на узел
	void setInit() 
	{
		flagInit = 1;
	};
};

class Tree
{
private:
	Node* node;
	Tree* up;
	Tree* left;
	Tree* right;
public:
	Tree();
	Tree(Tree*, Tree*, Tree*, Node*);
	~Tree();

	Tree* findMethod(const type_lex& lex);
	void PrintError(std::string errorMessage, std::string lexeme);

	void setLeft(Node*);
	void setRight(Node*);

	Tree* getLeft();
	Tree* getRight();
	Tree* getNode();
	type_object getSelfObjectType();
	Tree* getClassPointer();
	type_data getSelfDataType();
	std::string getSelfId();
	bool isSelfInit();

	Tree* findUp(Tree*, std::string);
	Tree* findUp(std::string);
	Tree* findUp(Tree*, std::string, type_object);
	Tree* findUp(std::string, type_object);
	Tree* findUp(Tree*, type_object);
	Tree* findUp(type_object);
	Tree* findUpOneLevel(Tree*, std::string);
	Tree* findRightLeft(Tree* from, std::string id);
	Tree* findRightLeft(std::string id);
	Tree* findLeft(Tree* from, std::string id);
	Tree* findLeft(std::string id);
	void SetInit();

	type_data getDataType(int);

	type_data getTypeResult(type_data, type_data, int);

	void print(int);
	void print();
	bool isDoublicateId(Tree*, std::string);
	bool isAllowChangeId(std::string);
	bool isMainExists();
	bool canBeAdded(type_data type1, type_data type2);
	bool canBeAdded(int type1, int type2);

};