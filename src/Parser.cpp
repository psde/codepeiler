#include "Parser.hpp"

#include <iostream>

struct Rule {
    int size;
    Token::TType* tokens;

    bool isTokenInRule(Token tok) const {
        for(int i=0; i<size; i++)
            if(tok.getType() == tokens[i])
                return true;
        return false;
    }
};

// TODO: Dear science, C is fugly as hell. Beautify this, asap.
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
const Rule RULE_PROGSTART = {
    sizeof(TOKENS_PROGSTART) / sizeof(TOKENS_PROGSTART[0]),
    TOKENS_PROGSTART
};

Parser::Parser(Lexer *lexer)
 : lexer(lexer)
{
    this->setup();    
}

Parser::~Parser()
{

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
    if(RULE_PROGSTART.isTokenInRule(currentToken))
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
