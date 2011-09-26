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
    ParserRule rule;
    char *message;

public:
    ParserError(Token tok, ParserRule rule, String customMsg = "")
     : tok(tok), rule(rule)
    {
        String msg = "Unexpected Token '";
        msg += tok.getTokenDescription();
        msg += "' in '";
        msg += rule.name;
        msg += "' at line ";
        msg += (long)tok.getLine();
        msg += ", column ";
        msg += (long)tok.getColumn();

        if(!(customMsg == ""))
        {
            msg += " - ";
            msg += customMsg;
        }

        message = new char[msg.length() + 1];
        for(unsigned int i=0; i<msg.length();i++)
            message[i] = msg[i];
        message[msg.length()] = '\0';
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

    Prog* parseProg();
    Decls* parseDecls();
    Decl* parseDecl();
    Statements* parseStatements();
    Statement* parseStatement();
    Exp* parseExp();
    Exp2* parseExp2();
    Index* parseIndex();
    OpExp* parseOpExp();
    Op* parseOp();

    void throwError(ParserRule rule = RULE_NONE, String msg = "");
public:

    Parser(Lexer *lexer);
    ~Parser();

    ParseTree *parse();
    
};

#endif
