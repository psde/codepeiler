#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"

// TODO: not allowed to use string
#include <string>

std::string LexerState_lookup[] =
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
    "STATE_SIGN_SEMICOLON",
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
    STATE_SIGN_SEMICOLON,
    STATE_NOSTATE
};

//#define LEXER_DEBUG

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

        this->addTransition(STATE_BEGIN, ';', STATE_SIGN_SEMICOLON);
        this->addFinalState(STATE_SIGN_SEMICOLON, Token::TOKEN_SEMICOLON);

        this->line = 1;
        this->column = 1;
        this->steps = 0;
    }

    int line;
    int column;
    int steps;

    unsigned char getChar()
    {
        this->steps++;
        this->column++;
        char c = this->buffer->getChar();

        return c;
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
            token.setPosition(this->line, this->column); 
            return token;
        }

        unsigned int state = STATE_BEGIN;
        unsigned int lastFinal = STATE_ERROR;

        char c;
        std::string lexem = "";

        int steps = 0;
		int lastFinalStep = 0;
        for(;;)
        {
            static int newLines = 0;

            for(int i=0; i != newLines; i++)
            {   
                this->line++;
                this->column = 1;
            }
            newLines = 0;


            do
            {
                c = this->getChar();//this->buffer->getChar();
                //steps++;

                /*if(c == '\n')
                {
                    this->line++;
                    this->column = 0;
                }*/

                if(c == '\n')
                {
                    newLines++;
                }

            } while(c == ' ' || c == '\n');

            // comment parsing
            if(c == '(' && this->buffer->peekChar() == '*')
            {
                //std::cout << "comment: " << c;
                while(this->buffer->peekChar() != 0x00)
                {
                    if(c == '*' && this->buffer->peekChar() == ')')
                        break;

                    //c = this->getChar(); //this->buffer->getChar();
                    c = this->buffer->getChar();
                    steps++;
                    //std::cout << c;
                }

                //c = this->getChar(); //this->buffer->getChar();
                c = this->buffer->getChar();
                steps++;
            
                //std::cout << c << std::endl;

               if(state == STATE_BEGIN)
                    continue;
                else
                    break;
            }

            unsigned int nextState = this->transitions[state][c];
            
            //lexem = lexem + c;

#ifdef LEXER_DEBUG            
            std::cout << LexerState_lookup[state] << " -- '" << c << "'[" << steps << "] --> " << LexerState_lookup[nextState] << std::endl;
#endif

            // Is final state? 
            if(this->finalState[state])
            {
                lastFinal = state;
				lastFinalStep = steps;
#ifdef LEXER_DEBUG
				std::cout << "^ This could be a final state! (steps: " << steps << ")"<< std::endl;
#endif
            }

            // Is transition possible?
            if(!nextState)
            {
#ifdef LEXER_DEBUG
                std::cout << "No transition possible." << std::endl;
#endif
                this->buffer->ungetChar(1);
                break;
            }

            state = nextState;

            lexem = lexem + c;
            /*if(c == '\n')
            {
                this->line++;
                this->column = 1;
            }*/
        }

        if(this->finalState[state])
        {
#ifdef LEXER_DEBUG
            std::cout << "We got a final state: " << LexerState_lookup[state] << std::endl;
#endif
            token.type(this->finalState[state]);
            token.lexem(lexem);
            token.setPosition(this->line, this->column - lexem.size() - 2);
        }
        else if(lastFinal != STATE_ERROR)
        {
#ifdef LEXER_DEBUG
            std::cout << "STATE_ERROR, unget" << std::endl;
#endif
            this->buffer->ungetChar(steps - lastFinalStep);
        }

        return token;
    }

};

#endif
