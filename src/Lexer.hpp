#ifndef LEXER_HPP
#define LEXER_HPP

#include <ctype.h>
#include "Token.hpp"
#include "BufferReader.hpp"
#include "String.hpp"

//#define LEXER_DEBUG

class Position
{
    public:
    unsigned int line, column;

    Position() : line(0), column(0) {};
};

class Lexer
{
private:
    enum LexerState
    {
        STATE_ERROR = 0,
        STATE_BEGIN,
        STATE_IDENTIFIER,
        STATE_INTEGER,
        STATE_SIGN_PLUS,
        STATE_SIGN_MINUS,
        STATE_SIGN_DIV,
        STATE_SIGN_MULT,
        STATE_SIGN_EQUAL,
        STATE_SIGN_LESSER,
        STATE_SIGN_GREATER,
        STATE_SIGN_SEMICOLON,
        STATE_SIGN_LER_INC,
        STATE_SIGN_LER,
        STATE_SIGN_PAREN_L,
        STATE_SIGN_PAREN_R,
        STATE_SIGN_BRACE_L,
        STATE_SIGN_BRACE_R,
        STATE_SIGN_BRACKET_L,
        STATE_SIGN_BRACKET_R,
        STATE_SIGN_NOT,
        STATE_SIGN_AND,
        STATE_NOSTATE
    };

    BufferReader *buffer;

    unsigned int transitions[STATE_NOSTATE+1][256];
    Token::TType finalState[STATE_NOSTATE+1];

    char currentChar;
    Position pos;
    unsigned int steps;

    void addTransition(LexerState from, char c, LexerState to);
    void addFinalState(LexerState from, Token::TType type);
    void addSolitaryState(LexerState to, char c, Token::TType type);

    void setup();

    void getChar();
    void ungetChar(unsigned int count);

    bool isComment();

public:
    Lexer(BufferReader *buffer);

    Token nextToken();
};

#endif
