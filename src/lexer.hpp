#ifndef LEXER_HPP
#define LEXER_HPP

#include <ctype.h>
#include "token.hpp"
#include "string.hpp"

String LexerStateStrings[] =
{
    "STATE_ERROR",
    "STATE_BEGIN",
    "STATE_IDENTIFIER",
    "STATE_INTEGER",
    "STATE_SIGN_PLUS",
    "STATE_SIGN_MINUS",
    "STATE_SIGN_DIV",
    "STATE_SIGN_MULT",
    "STATE_SIGN_EQUAL",
    "STATE_SIGN_LESSER",
    "STATE_SIGN_GREATER",
    "STATE_SIGN_SEMICOLON",
    "STATE_SIGN_LER_INC",
    "STATE_SIGN_LER",
    "STATE_SIGN_PAREN_L",
    "STATE_SIGN_PAREN_R",
    "STATE_SIGN_BRACE_L",
    "STATE_SIGN_BRACE_R",
    "STATE_SIGN_BRACKET_L",
    "STATE_SIGN_BRACKET_R",
    "STATE_SIGN_NOT",
    "STATE_SIGN_AND",
    "STATE_NOSTATE"
};

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
    Buffer *buffer;

    unsigned int transitions[STATE_NOSTATE+1][256];
    Token::TType finalState[STATE_NOSTATE+1];

    char currentChar;
    Position pos;
    unsigned int steps;

    void addTransition(LexerState from, char c, LexerState to)
    {
        this->transitions[from][c] = to;
    }

    void addFinalState(LexerState from, Token::TType type)
    {
        this->finalState[from] = type;
    }

    void addSolitaryState(LexerState to, char c, Token::TType type)
    {
        this->addTransition(STATE_BEGIN, c, to);
        this->addFinalState(to, type);
    }

    // Configures the state machine
    void setup()
    {
        // Reset all transitions and final states first
        for(unsigned int i = 0; i < STATE_NOSTATE; i++)
            memset(this->transitions[i], 0, sizeof(this->transitions[i]));
        memset(this->finalState, 0, sizeof(this->finalState));    


        for(unsigned char c = 'A'; c <= 'Z'; c++)
        {
            this->addTransition(STATE_BEGIN, c, STATE_IDENTIFIER);
            this->addTransition(STATE_IDENTIFIER, c, STATE_IDENTIFIER);

            this->addTransition(STATE_BEGIN, c + 32, STATE_IDENTIFIER);
            this->addTransition(STATE_IDENTIFIER, c + 32, STATE_IDENTIFIER);
        }

        for(unsigned char c = '0'; c <= '9'; c++)
        {
            this->addTransition(STATE_BEGIN, c, STATE_INTEGER);
            this->addTransition(STATE_INTEGER, c, STATE_INTEGER);
            this->addTransition(STATE_IDENTIFIER, c, STATE_IDENTIFIER);
        }

        this->addFinalState(STATE_IDENTIFIER, Token::TOKEN_IDENTIFIER);
        this->addFinalState(STATE_INTEGER, Token::TOKEN_INTEGER); 

        this->addTransition(STATE_SIGN_LESSER, '=', STATE_SIGN_LER_INC);
        this->addTransition(STATE_SIGN_LER_INC, '>', STATE_SIGN_LER);
        this->addFinalState(STATE_SIGN_LER, Token::TOKEN_LER);

        this->addSolitaryState(STATE_SIGN_PLUS, '+', Token::TOKEN_PLUS);
        this->addSolitaryState(STATE_SIGN_MINUS, '-', Token::TOKEN_MINUS);
        this->addSolitaryState(STATE_SIGN_DIV, '/', Token::TOKEN_DIV);
        this->addSolitaryState(STATE_SIGN_MULT, '*', Token::TOKEN_MULT);
        this->addSolitaryState(STATE_SIGN_LESSER, '<', Token::TOKEN_LESSER);
        this->addSolitaryState(STATE_SIGN_GREATER, '>', Token::TOKEN_GREATER);
        this->addSolitaryState(STATE_SIGN_EQUAL, '=', Token::TOKEN_EQUAL);
        this->addSolitaryState(STATE_SIGN_SEMICOLON, ';', Token::TOKEN_SEMICOLON);
        this->addSolitaryState(STATE_SIGN_PAREN_L, '(', Token::TOKEN_PAREN_L);
        this->addSolitaryState(STATE_SIGN_PAREN_R, ')', Token::TOKEN_PAREN_R);
        this->addSolitaryState(STATE_SIGN_BRACE_L, '{', Token::TOKEN_BRACE_L);
        this->addSolitaryState(STATE_SIGN_BRACE_R, '}', Token::TOKEN_BRACE_R);
        this->addSolitaryState(STATE_SIGN_BRACKET_L, '[', Token::TOKEN_BRACKET_L);
        this->addSolitaryState(STATE_SIGN_BRACKET_R, ']', Token::TOKEN_BRACKET_R);
        this->addSolitaryState(STATE_SIGN_NOT, '!', Token::TOKEN_NOT);
        this->addSolitaryState(STATE_SIGN_AND, '&', Token::TOKEN_AND);
    }

    void getChar()
    {
        this->steps++;
        this->pos.column++;
        this->currentChar = this->buffer->getChar();

        // skip this char, we don't need it
        if(this->currentChar == '\r')
        {
            this->currentChar = this->buffer->getChar();
        }

        if(this->currentChar == '\n')
        {
            this->pos.line++;
            this->pos.column = 0;
        }
    }

    void ungetChar(unsigned int count)
    {
        this->steps -= count + 1;
        this->pos.column -= count + 1;
        this->buffer->ungetChar(count + 1);
        this->getChar();
    }

public:
	
    Lexer(Buffer *buffer)
    {
        this->buffer = buffer;
        this->setup();

        this->pos.line = 1;
        this->pos.column = 0;

        this->getChar();

        this->steps = 0;
    }

    Token nextToken()
    {
        Token token;

        if(this->buffer->peekChar() == 0x00)
        {
            token.setType(Token::TOKEN_EOF);
            token.setPosition(this->pos.line, this->pos.column); 
            return token;
        }

        unsigned int state = STATE_BEGIN;
        unsigned int lastFinal = STATE_ERROR;
        Position lastPos = pos;

        String lexem = "";

        for(;;)
        {
            // Skip all whitespaces (spaces, tabs, etc...)
            bool skipped = false;
            while(isspace(currentChar))
            {
                this->getChar();
                skipped = true;
            }

            if(skipped)
            {
                if(state == STATE_BEGIN)
                    continue;
                break;
            }

            if(currentChar == '(' && this->buffer->peekChar() == '*')
            {
                int commentStart = this->pos.column;
                while(true)
                {
                    if(currentChar == '*' && this->buffer->peekChar() == ')')
                    {
                        this->getChar();
                        break;
                    }

                    this->getChar();

                    // TODO: Check if this maybe skips a token
                    if(currentChar == 0x00)
                    {
                        token.setType(Token::TOKEN_COMMENT_ERROR);
                        token.setPosition(this->pos.line, commentStart);
                        return token;
                    }
                }

                this->getChar();

                if(state == STATE_BEGIN)
                    continue;
                break;
            }

            unsigned int nextState = this->transitions[state][currentChar];

#ifdef LEXER_DEBUG            
            std::cout << LexerStateStrings[state] << " -- '" << currentChar << "' --> " << LexerStateStrings[nextState] << std::endl;
#endif

            if(nextState && this->finalState[nextState])
            {
                lastFinal = nextState;
                lastFinalSteps = steps;
#ifdef LEXER_DEBUG
                std::cout << LexerStateStrings[nextState] << " could be a final state!" << std::endl;
#endif
            }

            if(!nextState)
            {
#ifdef LEXER_DEBUG
                std::cout << "No transition possible." << std::endl;
#endif
                break;
            }

            lastPos = this->pos;
            state = nextState;
            lexem += currentChar;
            this->getChar();
        }

        if(this->finalState[state])
        {
#ifdef LEXER_DEBUG
            std::cout << "We got a final state: " << LexerStateStrings[state] << std::endl;
#endif
            token.setType(this->finalState[state]);
            token.setLexem(lexem);
            token.setPosition(lastPos.line, lastPos.column - (lexem.length() - 1));
        }
        else if(lastFinal != STATE_ERROR)
        {
            token.setType(this->finalState[lastFinal]); 
            token.setPosition(lastPos.line, lastPos.column - (lexem.length() - 1));
            lexem[lexem.length()-1] = '\0';
            token.setLexem(lexem);
            this->ungetChar(this->steps - lastFinalSteps - 1);
            this->pos = lastPos;
        }
        else
        {
            this->getChar();
        }

        return token;
    }

};

#endif
