#include "Parser.hpp"

#include <iostream>

Token::TType TOKENS_PROG[] =
{
    Token::TOKEN_PRINT,
    Token::TOKEN_READ,
    Token::TOKEN_INT,
    Token::TOKEN_IDENTIFIER,
    Token::TOKEN_IF,
    Token::TOKEN_WHILE,
    Token::TOKEN_EOF
};
const ParserRule RULE_PROG = {
    "RULE_PROG",
    sizeof(TOKENS_PROG) / sizeof(TOKENS_PROG[0]),
    TOKENS_PROG
};

Token::TType TOKENS_DECLS[] =
{
    Token::TOKEN_INT
};
const ParserRule RULE_DECLS = {
    "RULE_DECLS",
    sizeof(TOKENS_DECLS) / sizeof(TOKENS_DECLS[0]),
    TOKENS_DECLS
};

Token::TType TOKENS_DECL[] =
{
    Token::TOKEN_INT
};
const ParserRule RULE_DECL = {
    "RULE_DECL",
    sizeof(TOKENS_DECL) / sizeof(TOKENS_DECL[0]),
    TOKENS_DECL
};

Token::TType TOKENS_TYPE_INT[] =
{
    Token::TOKEN_INT
};
const ParserRule RULE_TYPE_INT = {
    "RULE_TYPE_INT",
    sizeof(TOKENS_TYPE_INT) / sizeof(TOKENS_TYPE_INT[0]),
    TOKENS_TYPE_INT
};

Token::TType TOKENS_STATEMENTS[] =
{
    Token::TOKEN_PRINT,
    Token::TOKEN_READ,
    Token::TOKEN_INT,
    Token::TOKEN_IDENTIFIER,
    Token::TOKEN_IF,
    Token::TOKEN_WHILE,
    Token::TOKEN_EOF
};
const ParserRule RULE_STATEMENTS = {
    "RULE_STATEMENTS",
    sizeof(TOKENS_STATEMENTS) / sizeof(TOKENS_STATEMENTS[0]),
    TOKENS_STATEMENTS
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
    std::cout << "Next token is: " << this->currentToken.getTokenDescription() << "@" << this->currentToken.getLine() << "," << this->currentToken.getColumn() << std::endl;
}

bool Parser::requireToken(Token::TType tok, bool readNext)
{
    bool isOk = false;
    if(currentToken.getType() == tok)
        isOk = true;

    if(readNext)
        this->nextToken();
}

ParseTree *Parser::parse()
{
    this->nextToken();
    
    return this->parseProg();
}

ParseTree *Parser::parseProg()
{
    if(RULE_PROG.isTokenValid(currentToken))
    {
        std::cout << "RULE_PROG" << std::endl;
        ParseTree *tree = this->buildTree(RULE_PROG);
        tree->addNode(this->parseDecls());
        tree->addNode(this->parseStatements());
        return tree;
    }
    throw std::runtime_error("todo...");
}

ParseTree *Parser::parseDecls()
{
    while(RULE_DECLS.isTokenValid(currentToken))
    {
        std::cout << "RULE_DECLS" << std::endl;
        this->parseDecl();
    }
    //throw std::runtime_error("todo...");
    return this->buildTree(RULE_DECLS);
}

ParseTree *Parser::parseDecl()
{
    if(RULE_DECL.isTokenValid(currentToken))
    {
        std::cout << "RULE_DECL" << std::endl;
        ParseTree *tree = this->buildTree(RULE_DECL);
        tree->addNode(this->buildTree(RULE_TYPE_INT));
        this->nextToken();
        
        // Identifier?
        if(currentToken.getType() == Token::TOKEN_IDENTIFIER)
        {
            this->nextToken();
        }
        // Array?
        else if(currentToken.getType() == Token::TOKEN_BRACKET_L)
        {
            // TODO
            this->nextToken();
            this->nextToken();
            this->nextToken();
        }
        else
        {
            throw std::runtime_error("todo...");
        }

        this->requireToken(Token::TOKEN_SEMICOLON, true);
        return NULL;
    }
    throw std::runtime_error("todo...");
    return this->buildTree(RULE_PROG);
}

ParseTree *Parser::parseStatements()
{
    std::cout << "RULE_STATEMENTS" << std::endl;
    return this->buildTree(RULE_PROG);
}
