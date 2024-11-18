#include "Tree.h"

Tree::Tree()
{
	up = NULL;
	left = NULL;
	right = NULL;
	node = NULL;
}

Tree::Tree(Tree* up, Tree* left, Tree* right, Node* node)
{
	this->up = up;
	this->left = left;
	this->right = right;
	this->node = new Node();
	if (node != NULL) memcpy(this->node, node, sizeof(Node));
}

Tree::~Tree()
{
	if (left != nullptr) delete left;
	if (right != nullptr) delete right;
	if (node != nullptr) delete node;
}

void Tree::PrintError(std::string errorMessage, std::string lexeme)
{
	std::cout << "Semant Error. " << errorMessage << " Find: " << lexeme << std::endl;
	exit(1);
}

void Tree::setLeft(Node* node)
{
	this->left = new Tree(this, NULL, NULL, node);
}

Tree* Tree::findMethod(const type_lex& lex) {
	Tree* currentNode = this;

	// Ïåðåáèðàåì óçëû â äåðåâå
	while (currentNode != nullptr) {
		if (currentNode->node != nullptr &&
			currentNode->node->id == lex &&
			currentNode->node->objectType == OBJ_FUNC) { // Ïðîâåðêà íà òèï îáúåêòà
			return currentNode; // Åñëè íàøëè ìåòîä, âåðíåì åãî
		}
		currentNode = currentNode->getRight(); // Ïðîäâèæåíèå ê ñëåäóþùåìó óçëó
	}
	return nullptr; // Ìåòîä íå íàéäåí
}

void Tree::setRight(Node* node)
{
	this->right = new Tree(this, NULL, NULL, node);
}

Tree* Tree::getLeft()
{
	return this->left;
}

Tree* Tree::getRight()
{
	return this->right;
}

Tree* Tree::getNode()
{
	return this->node->classPointer;
}

Tree* Tree::findUp(Tree* from, std::string id)
{
	Tree* current = from;

	while (current != NULL) {
		if (current->node != NULL) {
			if (id.compare(current->node->id) == 0) break;
		}
		current = current->up;
	}

	return current;
}

Tree* Tree::findUp(std::string id)
{
	return findUp(this, id);
}

Tree* Tree::findUp(Tree* from, std::string id, type_object type)
{
	Tree* current = from;

	while (current != NULL) {
		if (current->node != NULL) {
			if (id.compare(current->node->id) == 0 && type == current->node->objectType) break;
		}

		current = current->up;
	}

	return current;
}

Tree* Tree::findUp(std::string id, type_object type)
{
	return findUp(this, id, type);
}

Tree* Tree::findUp(Tree* from, type_object type)
{
	Tree* current = from;

	while (current != NULL) {
		if (current->node != NULL) {
			if (type == current->node->objectType) break;
		}

		current = current->up;
	}

	return current;
}

Tree* Tree::findUp(type_object type)
{
	return findUp(this, type);
}

Tree* Tree::findUpOneLevel(Tree* from, std::string id)
{
	Tree* current = from;

	while (current != NULL && current->up != NULL && current->up->right != current)
	{
		if (id.compare(current->node->id) == 0) {
			return current;
		}
		current = current->up;
	}
	return NULL;
}

Tree* Tree::findRightLeft(Tree* from, std::string id)
{
	Tree* curNode = from->right;
	while (curNode != NULL) {
		if (curNode->node != NULL) {
			if (id.compare(curNode->node->id) == 0) break;
		}

		curNode = curNode->left;
	}
	return curNode;
}

Tree* Tree::findRightLeft(std::string id)
{
	return findRightLeft(this, id);
}

Tree* Tree::findLeft(Tree* from, std::string id)
{
	Tree* current = from;

	while (current != NULL)
	{
		if (current->node != NULL)
			if (id.compare(current->node->id) == 0)
				break;

		current = current->left;
	}

	return current;
}

Tree* Tree::findLeft(std::string id)
{
	return findLeft(this, id);
}

type_data Tree::getDataType(int type)
{
	if (type == typeInt) return TYPE_INTEGER;
	if (type == typeShort) return TYPE_SHORT;
	if (type == typeLong) return TYPE_LONG;
	if (type == typeFloat) return TYPE_FLOAT;
	return TYPE_UNKNOWN;
}

type_data Tree::getTypeResult(type_data type1, type_data type2, int operation) {
	if (operation >= typeUnEq && operation <= typeMore) return TYPE_SHORT;
	//if (operation == typeMod && (type1 == TYPE_DOUBLE || type2 == TYPE_DOUBLE)) return TYPE_UNKNOWN;   !!!
	if (operation == typeMod && (type1 == TYPE_FLOAT || type2 == TYPE_FLOAT)) return TYPE_UNKNOWN;
	if (type1 >= type2) return type1;

	return type2;
}

void Tree::print() {
	if (node != NULL) {
		std::cout << "node: " << node->id << " ";
	}

	if (left != NULL) {
		std::cout << "left: " << left->node->id << " ";
		left->print(); // рекурсивный вызов для левого дочернего узла
	}

	if (right != NULL) {
		std::cout << "right: " << right->node->id << " ";
		right->print(); // рекурсивный вызов для правого дочернего
	}
	std::cout << std::endl;
}

void Tree::print(int level) {
	// Óâåëè÷èâàåì îòñòóï äëÿ îòîáðàæåíèÿ èåðàðõèè
	std::string indent(level * 2, ' ');

	if (node != NULL) {
		if (node->id == "")
			std::cout << "Node: " << "\n";
		else
			std::cout << "Node: " << node->id << "\n";
	}
	else
	{
		std::cout << indent << "Node: \n";
	}
	if (right != NULL) {

		std::cout << indent << "Right -> ";

		right->print(level + 1); // ðåêóðñèâíûé âûçîâ äëÿ ïðàâîãî äî÷åðíåãî óçëà

	}
	if (left != NULL) {
		std::cout << indent << "Left -> ";
		left->print(level + 1); // ðåêóðñèâíûé âûçîâ äëÿ ëåâîãî äî÷åðíåãî óçëà

	}
}


bool Tree::isDoublicateId(Tree* addr, std::string id) {
	if (findUpOneLevel(addr, id) == NULL) return false;
	return true;
}

bool Tree::isAllowChangeId(std::string id) {
	Tree* node = findUp(id);

	//if (node->node->objectType != OBJ_VAR && node->node->objectType != OBJ_CLASS_OBJ) return false;  !!
	if (node->node->objectType != OBJ_VAR)
		return false;
	return true;
}

bool Tree::isMainExists() {
	Tree* root = this;

	while (root->up != NULL) root = root->up;

	Tree* main = root->findLeft("main");

	if (main == NULL) return false;
	return true;
}

type_object Tree::getSelfObjectType()
{
	return node->objectType;
}

Tree* Tree::getClassPointer()
{
	return node->pointer;
}

type_data Tree::getSelfDataType()
{
	return node->dataType;
}

std::string Tree::getSelfId()
{
	return node->id;
}

bool Tree::isSelfInit()
{
	return node->flagInit;
}

bool Tree::canBeAdded(type_data type1, type_data type2) {
	// Äëÿ ïðèìåðà: òîëüêî ÷èñëîâûå òèïû ìîæíî ñêëàäûâàòü
	if ((type1 == typeInt || type1 == typeFloat) &&
		(type2 == typeInt || type2 == typeFloat)) {
		return true;
	}
	return false;
}

bool Tree::canBeAdded(int type1, int type2) {
	// Äëÿ ïðèìåðà: òîëüêî ÷èñëîâûå òèïû ìîæíî ñêëàäûâàòü
	if ((type1 == typeInt || type1 == typeFloat) &&
		(type2 == typeInt || type2 == typeFloat)) {
		return true;
	}
	return false;
}