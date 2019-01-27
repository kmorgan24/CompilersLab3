#pragma once

// print an error in a standard form
void Error(std::string expecting);

// Peek at the next token without advancing the file
int PeekToken();

// Advance the file and return the next token
int AdvanceToken();
