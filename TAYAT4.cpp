#include <iostream>
#include <iomanip>
#include "Scaner.h"

int main(int argc, char* argv[])
{
    Scaner* scaner;
    int type;
    type_lex lex;

    if (argc <= 1)
        scaner = new Scaner("input.txt");
    else
        scaner = new Scaner(argv[1]);
    do
    {
        type = scaner->UseScaner(lex);
        std::cout << std::setw(32) << lex << "   type of:    " << type << std::endl;
    } while (type != typeEnd);

    delete scaner;
    return 0;
}
