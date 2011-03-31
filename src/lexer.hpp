#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include "string.hpp"

String LexerState_lookup[] =
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

    void addSolitaryState(LexerState to, char c, Token::TType type)
    {
        this->addTransition(STATE_BEGIN, c, to);
        this->addFinalState(to, type);
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

        // TODO: Figure out a way on how to beautify this.
        this->addFinalState(STATE_IDENTIFIER, Token::TOKEN_IDENTIFIER);
        this->addFinalState(STATE_INTEGER, Token::TOKEN_INTEGER); 

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

        this->line = 1;
        this->column = 1;
        this->startColumn = 1;
        this->steps = 0;
    }

    int line;
    int column;
    int startColumn;
    int steps;

    unsigned char getChar()
    {
        this->steps++;
        this->column++;
        char c = this->buffer->getChar();

        return c;
    }

    void skipChar()
    {
        this->steps++;
        //this->column++;
        char c = this->buffer->getChar();
    }

    void ungetChar(unsigned int count)
    {
        this->column -= count;
        this->steps -= count;
        this->buffer->ungetChar(count);
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
        String lexem = "";

//        int steps = 0;
//        int startColumn = this->column;

        static int foo = 0;
        startColumn = this->column + foo;
        foo = 0;
#ifdef LEXER_DEBUG
        std::cout << "Setting startColum to: " << startColumn << std::endl;
#endif
        int lastFinalStep = this->steps;
        for(;;)
        {
            static int newLines = 0;

            for(int i=0; i != newLines; i++)
            {   
                this->line++;
                this->column = 1;
                this->startColumn = 1;
#ifdef LEXER_DEBUG
                std::cout << "newLine detected, column=" << this->column << " line=" << this->line << std::endl;
#endif
            }
            newLines = 0;

            /*c = this->getChar();

            bool specialChars = false;
            while(c == ' ' || c == '\n')
            {
                if(c == '\n')
                    newLines++;

                specialChars = true;
                c = this->getChar();
            }*/       
            
            /*if(specialChars && state == STATE_BEGIN)
                break;            */

            do
            {
                c = this->getChar();

                if(c == '\n')
                {
                    newLines++;
                }

                if(c == ' ' && state != STATE_BEGIN)
                {
                    foo++;
                    break;
                }

            } while(c == ' ' || c == '\n');

            // comment parsing
            if(c == '(' && this->buffer->peekChar() == '*')
            {
                int commentStart = this->column;
                while(true /*this->buffer->peekChar() != 0x00*/)
                {
                    if(c == '*' && this->buffer->peekChar() == ')')
                        break;

                    c = this->getChar();

                    if(c == 0x00)
                    {
                        token.type(Token::TOKEN_COMMENT_ERROR);
                        token.setPosition(this->line, commentStart);
                        return token;
                    }
                }

                //this->skipChar();
                c = this->getChar();
 
                if(state == STATE_BEGIN)
                    continue;
                else
                    break;
            }

            unsigned int nextState = this->transitions[state][c];

#ifdef LEXER_DEBUG            
            std::cout << LexerState_lookup[state] << " -- '" << c << "'[" << steps << "] --> " << LexerState_lookup[nextState] << " StartColumn: " << this->startColumn << std::endl;
#endif

            // Is final state? 
            if(nextState && this->finalState[nextState])
            {
                lastFinal = nextState;
                lastFinalStep = steps;
#ifdef LEXER_DEBUG
                std::cout << LexerState_lookup[nextState] << " could be a final state! (steps: " << steps << ")"<< std::endl;
#endif
            }

            // Is transition possible?
            if(!nextState)
            {
#ifdef LEXER_DEBUG
                std::cout << "No transition possible." << std::endl;
#endif
                this->ungetChar(1);
                //this->buffer->ungetChar(steps - lastFinalStep);
                //std::cout << steps-lastFinalStep << std::endl;
                break;
            }

            state = nextState;

            lexem += c;
        }

        if(this->finalState[state])
        {
#ifdef LEXER_DEBUG
            std::cout << "We got a final state: " << LexerState_lookup[state] << std::endl;
#endif
            token.type(this->finalState[state]);
            token.lexem(lexem);
            token.setPosition(this->line, startColumn);
        }
        else if(lastFinal != STATE_ERROR)
        {
#ifdef LEXER_DEBUG
            std::cout << "STATE_ERROR, unget " << steps - lastFinalStep << std::endl;
#endif
            this->ungetChar(steps - lastFinalStep);
        }
        else
        {
            std::cout << "what" << std::endl;
        }

        return token;
    }

};

#endif
