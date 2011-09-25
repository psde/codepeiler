#ifndef PARSER_HPP
#define PARSER_HPP

#include <exception>
#include "ParserRule.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "ParseTree.hpp"
#include "List.hpp"
#include "Token.hpp"
#include "String.hpp"

class ParserError : public std::exception
{
private:
    Token tok;
    char *message;

public:
    ParserError(Token tok, String customMsg = "")
     : tok(tok)
    {
        String msg = "Unexpected Token ";
        msg += tok.getTokenDescription();
        msg += " Line: ";
        msg += (long)tok.getLine();
        msg += " Column: ";
        msg += (long)tok.getColumn();

        if(!(customMsg == ""))
        {
            msg += " ";
            msg += customMsg;
        }

        message = new char[msg.length() + 1];
        for(int i=0; i<msg.length();i++)
            message[i] = msg[i];
        message[msg.length() + 1] = '\0';
    }

    Token getToken() { return this->tok; }

    ~ParserError() throw() 
    { }

    virtual const char* what() const throw() 
    {
        return message;
    }

};

class Parser
{
private:

    Lexer *lexer;
    Token currentToken;
    void nextToken();
    bool requireToken(Token::TType tok, bool readNext = false);

    ParseTree *buildTree(ParserRule rule);

    ParseTree *parseProg();
    ParseTree *parseDecls();
    ParseTree *parseDecl();
    ParseTree *parseArray();
    ParseTree *parseStatements();
    ParseTree *parseStatement();
    ParseTree *parseExp();
    ParseTree *parseExp2();
    ParseTree *parseIndex();
    ParseTree *parseOpExp();
    ParseTree *parseOp();

public:

    Parser(Lexer *lexer);
    ~Parser();

    ParseTree *parse();
    
};

#endif
