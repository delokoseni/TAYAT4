#include "Scaner.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <fstream>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Scaner* scaner;
    int type;
    type_lex lex;
    scaner = new Scaner("input.txt");

    do
    {
        type = scaner->UseScaner(lex);
        std::cout << std::setw(16) << lex << "\tпринадлежит к типу №\t" << type << std::endl;
    } while (type != typeEnd);

    delete scaner;
    return 0;
}
