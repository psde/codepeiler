#ifndef ENTRY_HPP
#define ENTRY_HPP

#include "token.hpp"
#include "string.hpp"

class Entry
{

public:
    Token::TType type;
    String lexem;

    Entry(Token::TType t, String l)
    {
        this->type = t;
        this->lexem = l;
    }
};

#endif
