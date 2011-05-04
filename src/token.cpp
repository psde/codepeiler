#include "token.hpp"

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

Token::Token(TType type, int line, int column)
{
    this->tokenType = type;
    this->lineNumber = line;
    this->columnNumber = column;
    this->lexemName = "";
}

Token::Token()
{
    this->tokenType = Token::TOKEN_INVALID;
    this->lineNumber = -1;
    this->columnNumber = -1;
}

String Token::getTokenDescription()
{
    return TTypeStrings[this->tokenType];
}

void Token::setPosition(int line, int column)
{
    this->lineNumber = line;
    this->columnNumber = column;
}

void Token::setEntry(Entry* e)
{
    this->entry = e;
}

Entry* Token::getEntry()
{
    return this->entry;
}

String Token::getLexem()
{
    return this->lexemName;
}

void Token::setLexem(String lexem)
{
    this->lexemName = lexem;
}

int Token::getLine()
{
    return this->lineNumber;
}

int Token::getColumn()
{
    return this->columnNumber;
}

Token::TType Token::getType()
{
    return this->tokenType;
}

void Token::setType(TType token)
{
    this->tokenType = token;
}
