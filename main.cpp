// Main routine for lang compiler.
// This version only runs the lexer
//
// Author: Phil Howard
// phil.howard@oit.edu
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include "lex.h"
#include "parse.h"

int main(int argc, char **argv)
{
    const char *outfile_name;
    int result = 0;

    if (argc > 1)
    {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL)
        {
            std::cerr << "Unable to open file " << argv[1] << "\n";
            exit(-1);
        }
    }

    if (argc > 2)
        outfile_name = argv[2];
    else
        outfile_name = "/dev/tty";

    FILE *output = fopen(outfile_name, "w");
    if (output == nullptr)
    {
        std::cerr << "Unable to open output file " << outfile_name << "\n";
        exit(-1);
    }

    // redirect stdout to the output file
    int output_fd = fileno(output);
    if (dup2(output_fd, 1) != 1)
    {
        std::cerr << "Unable configure output stream\n";
        exit(-1);
    }

    if (FindPROG())
    {
        std::cout << "Found a Program\n";
    }

    if (yylex() != 0)
    {
        std::cout << "Junk at end of program\n";
    }

    return result;
}
