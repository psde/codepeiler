#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

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
    STATE_SIGN_SEMICOLON,
    STATE_NOSTATE
};


class Lexer
{
private:
    Buffer *buffer;

    unsigned int transitions[STATE_NOSTATE+1][256];
    TType finalState[STATE_NOSTATE+1];

    void addTransition(LexerState from, char c, LexerState to)
    {
        this->transitions[from][c] = to;
    }

    void addFinalState(LexerState from, TType type)
    {
        this->finalState[from] = type;
    }

    void setup()
    {
        for(unsigned char c = 'a'; c <= 'Z'; c++)
        {
            this->addTransition(STATE_BEGIN, c, STATE_IDENTIFIER);
            this->addTransition(STATE_IDENTIFIER, c, STATE_IDENTIFIER);
        }

        for(unsigned char c = '0'; c <= '9'; c++)
        {
            this->addTransition(STATE_BEGIN, c, STATE_INTEGER);
            this->addTransition(STATE_INTEGER, c, STATE_INTEGER);
        }
    }

public:
	
    Lexer(Buffer *buffer)
    {
        this->buffer = buffer;
        this->setup();
    }

    Token nextToken()
    {

    }

};

#endif
