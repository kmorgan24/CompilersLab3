//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab2
//
// Author: Kyronn Morgan
//
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"
void Recover()
{
     
    while (PeekToken() != ';' && PeekToken() != 0 && PeekToken() != END)
    {
        AdvanceToken();
    }
    if(PeekToken() == ';' )
    {
        AdvanceToken();
        FindSTMT();
    }
}
//*******************************************
// Find a PROG non-terminal
bool FindPROG()
{
	//PROG  -> STMTS end
    if(!FindSTMTS())
        return false;
    if(PeekToken() != END)
        return false;
    AdvanceToken();
       return true;
}
/*******************************************
bool FindExample()
{
    if (!FindPART1()) return false;
    
    int token = PeekToken();
    if (token != '+') return false;
    AdvanceToken();         // past '+'

    if (!FindPART2()) return false;

    return true;
}
*/
bool FindSTMTS()
{
    //STMT  -> EXPR ;
    while (FindSTMT())
    { 

    }
    return true;
}
bool FindSTMT()
{
    //STMT  -> EXPR ;
    if(!FindEXPR())
    {
         Recover();
         if(PeekToken() == 0 || PeekToken() == END)   
             return false;
         else 
             return true;
    }
  
    if(PeekToken() != ';')
    {
        Error("';'");
        Recover();
        if(PeekToken() == END || PeekToken() == 0)
             return false;
        else
             return true;
    }
    else
    {
        std::cout << "Found a statement" << std::endl;
        AdvanceToken();
        return true;
    }

}
bool FindEXPR()
{
    //EXPR  -> (EXPR) EXPR’
    //      -> TERM
    if(PeekToken() == '(')
    {
       AdvanceToken();
       if(!FindEXPR())
           return false;
       if(PeekToken() != ')')
       {
           Error("')'");
           return false;
       }
       AdvanceToken();
       FindEXPR_P();
   }
   else if(!FindTERM())
       return false;
   return true;
}

bool FindEXPR_P()
{
    //EXPR’ -> PLUSOP (EXPR) EXPR’
    //      -> λ
    if(FindPLUSOP())
    {
      if(PeekToken() != '(')
      {
          Error("'('");
          return true;
      }
      AdvanceToken();
      if(!FindEXPR())
          return false;
      if(PeekToken() != ')')
      {
          Error("')'");
          return false;
      }
      AdvanceToken(); 
      FindEXPR_P();
    }
    return true;
}

bool FindPLUSOP()
{
    //PLUSOP -> +
    //       -> -
    if(PeekToken() == '+' || PeekToken() == '-')
    {
        AdvanceToken();
        return true;
    }
    else
        return false;
}

bool FindTERM()
{
    //TERM  -> [EXPR] TERM’
    //      -> num
    if(PeekToken() == '[')
    {
        AdvanceToken();
        if(!FindEXPR())
            return false;
        if(PeekToken() != ']')
        {
            Error("']'");
            return false;
        }
        AdvanceToken();
        if(!FindTERM_P())
            return false;
        else 
            return true;
   }
   else if(PeekToken() == INT_VAL )
   {
       AdvanceToken();
       return true;
   }
   else
       return false;
}

bool FindTERM_P()
{
    //TERM’ -> TIMESOP [EXPR] TERM’
    //      -> λ
    if(FindTIMESOP())
    {
        if(PeekToken() != '[')
        {
             Error("'['");
             return false;
        }
        AdvanceToken();
        if(!FindEXPR())
             return false;
        if(PeekToken() != ']')
        {
             Error("']'");     
             return false;
        }
        AdvanceToken();
        FindTERM_P();
    }
    return true;
}


bool FindTIMESOP()
{
    //TIMESOP -> *
    //        -> /
    if(PeekToken() == '*' || PeekToken() == '/')
    {
        AdvanceToken();
        return true;
    }
    else
        return false;
}






