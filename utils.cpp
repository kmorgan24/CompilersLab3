#include <iostream>
#include "lex.h"
#include "utils.h"

// remember a peeked token
static int g_token = -1;

//*******************************************
// Print an error message in a standard form
void Error(std::string expecting)
{
    std::cout << "Found '" << yytext << "' when expecting a " << expecting;
    std::cout << " in line " << yylineno << std::endl;
}
//*******************************************
// Peek at the next token without advancing through the file
int PeekToken()
{
    if (g_token < 0) g_token = yylex();

    return g_token;
}
//*******************************************
// Read the next token in the file and return it.
int AdvanceToken()
{
    g_token = yylex();

    return g_token;
}
