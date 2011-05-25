#include "Parser.hpp"

Parser::Parser(Lexer *lexer)
 : lexer(lexer)
{
    
}

Parser::~Parser()
{

}

void Parser::nextToken()
{
    this->currentToken = this->lexer->nextToken();
}

ParseTree *Parser::parse()
{
    this->nextToken();
    return this->parseProg();
}

ParseTree *Parser::parseProg()
{
    return new ParseTree();
}
