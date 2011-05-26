#include "Parser.hpp"

#include <iostream>

Token::TType TOKENS_PROGSTART[] =
{
    Token::TOKEN_PRINT,
    Token::TOKEN_READ,
    Token::TOKEN_INT,
    Token::TOKEN_IDENTIFIER,
    Token::TOKEN_IF,
    Token::TOKEN_WHILE,
    Token::TOKEN_EOF
};
const ParserRule RULE_PROGSTART = {
    "RULE_PROGSTART",
    sizeof(TOKENS_PROGSTART) / sizeof(TOKENS_PROGSTART[0]),
    TOKENS_PROGSTART
};

Parser::Parser(Lexer *lexer)
 : lexer(lexer)
{

}

Parser::~Parser()
{

}

ParseTree *Parser::buildTree(ParserRule rule)
{
    return new ParseTree(rule, currentToken.getLine(), currentToken.getColumn());
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
    if(RULE_PROGSTART.isTokenValid(currentToken))
    {
        std::cout << "Seems like it is in RULE_PROGSTART..." << std::endl;
        this->parseDecls();
        this->parseStatements();
    }

    return this->buildTree(RULE_PROGSTART);
}

ParseTree *Parser::parseDecls()
{
    return this->buildTree(RULE_PROGSTART);
}

ParseTree *Parser::parseStatements()
{
    return this->buildTree(RULE_PROGSTART);
}
