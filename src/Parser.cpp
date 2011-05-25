#include "Parser.hpp"

#include <iostream>

// TODO: Dear science, C is fugly as hell. Beautify this, asap.
int SIZE_RULE_PROGSTART = 7;
Token::TType RULE_PROGSTART[] =
{
    Token::TOKEN_PRINT,
    Token::TOKEN_READ,
    Token::TOKEN_INT,
    Token::TOKEN_IDENTIFIER,
    Token::TOKEN_IF,
    Token::TOKEN_WHILE,
    Token::TOKEN_EOF
};

Parser::Parser(Lexer *lexer)
 : lexer(lexer)
{
    this->setup();    
}

Parser::~Parser()
{

}

bool Parser::isTokenInRule(Token tok, Token::TType *rule, int size)
{
    for(int i=0; i<size; i++)
    {
        if(tok.getType() == rule[i])
            return true;
    }
    return false;
}

void Parser::setup()
{
    
}

void Parser::nextToken()
{
    this->currentToken = this->lexer->nextToken();
    std::cout << "Next token is: " << this->currentToken.getTokenDescription() << std::endl;
}

ParseTree *Parser::parse()
{
    this->nextToken();
    return this->parseProg();
}

ParseTree *Parser::parseProg()
{ 
    if(this->isTokenInRule(currentToken, RULE_PROGSTART, SIZE_RULE_PROGSTART))
    {
        std::cout << "Seems like it is in RULE_PROGSTART..." << std::endl;
        this->parseDecls();
        this->parseStatements();
    }

    return new ParseTree();
}

ParseTree *Parser::parseDecls()
{
    return new ParseTree();
}

ParseTree *Parser::parseStatements()
{
    return new ParseTree();
}
