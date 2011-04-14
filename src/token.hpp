#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include "string.hpp"

// TODO: Not allowed to use std::string
String TType_lookupTable[] = 
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
        TOKEN_EOF
    };

private:

	TType tokenType;
	int lineNumber;
	int columnNumber;
    String lexemName;

public:

    // TODO: Not allowed to use std::string
    String echo()
    {
        return TType_lookupTable[this->tokenType];
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

    String lexem()
    {
        return this->lexemName;
    }

    void lexem(String lexem)
    {
        this->lexemName = lexem;

        if(this->type() != Token::TOKEN_IDENTIFIER)
            return;

        // TODO: Kerl sayz: ich finde, print sollte kein eigenständiges token sein. (2011-03-31 23:30) 
        // TODO: ^ maybe do this for assignment #2
        if(lexem == "print")
        {
            this->type(Token::TOKEN_PRINT);
        }

        if(lexem == "read")
        {
            this->type(Token::TOKEN_READ);
        }
    }

	int line()
	{	
		return this->lineNumber;
	}

	int column()
	{
		return this->columnNumber;
	}

	TType type()
	{
		return this->tokenType;
	}

    void type(TType token)
    {
        this->tokenType = token;
    }
};

#endif
