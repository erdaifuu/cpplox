#include <iostream>
#include <ostream>

#include "lox.h"

int main(int argc, char* argv[])
{
    if (argc > 2)
    {
        std::cout << "Usage: clox [script]" << std::endl;
        return 64;
    }
    if (argc == 2)
    {
        run_file(argv[1]);
    }
    else
    {
        run_prompt();
    }
    return 0;
};