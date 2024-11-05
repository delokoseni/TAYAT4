#pragma once

#include "Scaner.h"

enum type_data {
	TYPE_UNKNOWN = 0,
	TYPE_INT = 1,
	TYPE_SHORT = 2,
	TYPE_LONG = 3,
	TYPE_FLOAT = 4
};

enum type_object {
	OBJECT_UNKNOWN = 0,
	OBJECT_VARIABLE = 1,
	OBJECT_FUNCTION = 2
};

class Tree;

struct Node {
	type_lex lex;
	type_object object;
	type_data type;
	int init;
	int array_size;
	Tree* pointer;
};

class Tree {
private:
	Scaner* scaner;
	Node* node;
	Tree* parent;
	Tree* left;
	Tree* right;
public:
	Tree* current;
	Tree(Scaner*, Tree* parent, Tree* left, Tree* right, Node* node);
	Tree(Scaner*);
	~Tree();

	void set_left(Node*);
	void set_right(Node*);
	Tree* find_up(Tree*, type_lex);
	Tree* find_up(type_lex);
	Tree* find_up_at_level(Tree*, type_lex);
	Tree* find_right_left(Tree*, type_lex);
	Tree* find_right_left(type_lex);

	void print();
	Node* get_node();
	void set_node(Node* node);
	Tree* semantic_include(type_lex, type_object, type_data);
	void set_current(Tree* tree);
	Tree* get_current();
	void semantic_set_type(Tree*, type_data);
	Tree* semantic_get_type(type_lex, type_object);
	void semantic_set_object(Tree*, type_object);
	Tree* semantic_get_object(type_lex);
	void semantic_set_init(Tree*, int);
	Tree* semantic_get_init(type_lex);


	int is_exists(Tree* tree, type_lex lex);
};