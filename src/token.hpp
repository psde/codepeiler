#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include "string.hpp"

class Entry;

String TTypeStrings[] =
{
    "TOKEN_INVALID",
    "TOKEN_COMMENT_ERROR",
    "TOKEN_IDENTIFIER",
    "TOKEN_INTEGER",
    "TOKEN_PLUS",
    "TOKEN_MINUS",
    "TOKEN_DIV",
    "TOKEN_MULT",
    "TOKEN_EQUAL",
    "TOKEN_LESSER",
    "TOKEN_GREATER",
    "TOKEN_SEMICOLON",
    "TOKEN_LER",
    "TOKEN_PAREN_L",
    "TOKEN_PAREN_R",
    "TOKEN_BRACE_L",
    "TOKEN_BRACE_R",
    "TOKEN_BRACKET_L",
    "TOKEN_BRACKET_R",
    "TOKEN_NOT",
    "TOKEN_AND",
    "TOKEN_READ",
    "TOKEN_PRINT",
    "TOKEN_IF",
    "TOKEN_ELSE",
    "TOKEN_WHILE",
    "TOKEN_INT",
    "TOKEN_EOF"
};


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

    String getTokenDescription()
    {
        return TTypeStrings[this->tokenType];
    }

    Token(TType type, int line, int column)
    {
        this->tokenType = type;
        this->lineNumber = line;
        this->columnNumber = column;
        this->lexemName = "";
    }

    Token()
    {
        this->tokenType = Token::TOKEN_INVALID;
        this->lineNumber = -1;
        this->columnNumber = -1;
    }

    void setPosition(int line, int column)
    {
        this->lineNumber = line;
        this->columnNumber = column;
    }

    void setEntry(Entry* e)
    {
        this->entry = e;
    }

    Entry* getEntry()
    {
        return this->entry;
    }

    String getLexem()
    {
        return this->lexemName;
    }

    void setLexem(String lexem)
    {
        this->lexemName = lexem;
    }

    int getLine()
    {
        return this->lineNumber;
    }

    int getColumn()
    {
        return this->columnNumber;
    }

    TType getType()
    {
        return this->tokenType;
    }

    void setType(TType token)
    {
        this->tokenType = token;
    }
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
