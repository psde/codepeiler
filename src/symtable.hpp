#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include "hashtable.hpp"
#include "entry.hpp"

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
    }
};

#endif
