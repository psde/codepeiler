#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include "String.hpp"

class Entry;

class Token
{
public:
    enum TType
    {
        TOKEN_INVALID = 0,
        TOKEN_COMMENT_ERROR,
        TOKEN_IDENTIFIER,
        TOKEN_INTEGER,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_DIV,
        TOKEN_MULT,
        TOKEN_EQUAL,
        TOKEN_LESSER,
        TOKEN_GREATER,
        TOKEN_SEMICOLON,
        TOKEN_LER,
        TOKEN_PAREN_L,
        TOKEN_PAREN_R,
        TOKEN_BRACE_L,
        TOKEN_BRACE_R,
        TOKEN_BRACKET_L,
        TOKEN_BRACKET_R,
        TOKEN_NOT,
        TOKEN_AND,
        TOKEN_READ,
        TOKEN_PRINT,
        TOKEN_IF,
        TOKEN_ELSE,
        TOKEN_WHILE,
        TOKEN_INT,
        TOKEN_EOF
    };

private:

    TType tokenType;
    int lineNumber;
    int columnNumber;
    String lexemName;

    Entry* entry;

public:

    Token(TType type, int line, int column);
    Token();

    String getTokenDescription();

    void setPosition(int line, int column);

    void setEntry(Entry* e);
    Entry* getEntry();

    unsigned long getULong();
    String getLexem();
    void setLexem(String lexem);

    int getLine();
    int getColumn();

    Token::TType getType();
    void setType(TType token);
};


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
