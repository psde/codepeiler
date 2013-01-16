#pragma once

#include "Hashtable.hpp"
#include "Token.hpp"

class Symtable : public Hashtable<Entry*>
{
public:
    Symtable(int i) : Hashtable<Entry*>(i) 
    {
        this->initSymbols();
    };    

    /*
      Adds symbols to the symtable, this is used so that the lexer does not
      has to keep track of these. Lexer reads these as "identifier", the
      symtable overrides it with this existing tokens.
    */
    void initSymbols()
    {
        this->put("print", new Entry(Token::TOKEN_PRINT, "print"));
        this->put("read", new Entry(Token::TOKEN_READ, "read"));
        this->put("if", new Entry(Token::TOKEN_IF, "if"));
        this->put("else", new Entry(Token::TOKEN_ELSE, "else"));
        this->put("while", new Entry(Token::TOKEN_WHILE, "while"));
        this->put("int", new Entry(Token::TOKEN_INT, "int"));
    }
};
