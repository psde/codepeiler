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
    Token::TType finalState[STATE_NOSTATE+1];

    void addTransition(LexerState from, char c, LexerState to)
    {
        this->transitions[from][c] = to;
    }

    void addFinalState(LexerState from, Token::TType type)
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
            this->addTransition(STATE_IDENTIFIER, c, STATE_IDENTIFIER);
        }

        this->addFinalState(STATE_IDENTIFIER, Token::TOKEN_IDENTIFIER);
        this->addFinalState(STATE_INTEGER, Token::TOKEN_INTEGER); 


        this->addTransition(STATE_BEGIN, '+', STATE_SIGN_PLUS);
        this->addFinalState(STATE_SIGN_PLUS, Token::TOKEN_PLUS);

        this->addTransition(STATE_BEGIN, '-', STATE_SIGN_MINUS);
        this->addFinalState(STATE_SIGN_MINUS, Token::TOKEN_MINUS);

        this->addTransition(STATE_BEGIN, '/', STATE_SIGN_DIV);
        this->addFinalState(STATE_SIGN_DIV, Token::TOKEN_DIV);

        this->addTransition(STATE_BEGIN, '*', STATE_SIGN_MULT);
        this->addFinalState(STATE_SIGN_MULT, Token::TOKEN_MULT);

        this->addTransition(STATE_BEGIN, '=', STATE_SIGN_EQUAL);
        this->addFinalState(STATE_SIGN_EQUAL, Token::TOKEN_EQUAL);
    }

public:
	
    Lexer(Buffer *buffer)
    {
        this->buffer = buffer;
        this->setup();
    }

    Token nextToken()
    {
        Token token;
       
        // check for EOF
        if(this->buffer->peekChar() == 0x00)
        {
            token.type(Token::TOKEN_EOF);
            token.setPosition(0, 0);    
            return token;
        }

        unsigned int state = STATE_BEGIN;
        unsigned int lastFinal = STATE_ERROR;

        char c;

        for(;;)
        {
            c = this->buffer->getChar();

            // comment parsing
            if(c == '(' && this->buffer->peekChar() == '*')
            {
                std::cout << "comment: " << c;
                while(this->buffer->peekChar() != 0x00)
                {
                    if(c == '*' && this->buffer->peekChar() == ')')
                        break;

                    c = this->buffer->getChar();
                    std::cout << c;
                }
                std::cout << this->buffer->peekChar() << std::endl;
            }
        }

        return token;
    }

};

#endif
