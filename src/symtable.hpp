#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include "hashtable.hpp"
#include "token.hpp"

class Symtable : public Hashtable<Entry*>
{
public:
    Symtable(int i) : Hashtable<Entry*>(i) 
    {
        this->initSymbols();
    };    

    void initSymbols()
    {
        this->put("print", new Entry(Token::TOKEN_PRINT, "print"));
        this->put("read", new Entry(Token::TOKEN_READ, "read"));
        /*this->put("if", new Entry(Token::TOKEN_IF, "if"));
        this->put("else", new Entry(Token::TOKEN_ELSE, "else"));
        this->put("while", new Entry(Token::TOKEN_WHILE, "while"));
        this->put("int", new Entry(Token::TOKEN_INT, "int"));*/
    }
};

#endif
