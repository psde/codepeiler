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

const ParserRule RULE_DECL = {
    "RULE_DECL",
    sizeof(TOKENS_DECLS) / sizeof(TOKENS_DECLS[0]),
    TOKENS_DECLS
};

const ParserRule RULE_TYPE_INT = {
    "RULE_TYPE_INT",
    sizeof(TOKENS_DECLS) / sizeof(TOKENS_DECLS[0]),
    TOKENS_DECLS
};

Token::TType TOKENS_STATEMENTS[] =
{
    Token::TOKEN_PRINT,
    Token::TOKEN_READ,
    Token::TOKEN_IDENTIFIER,
    Token::TOKEN_IF,
    Token::TOKEN_ELSE,
    Token::TOKEN_WHILE,
    Token::TOKEN_EOF
};
const ParserRule RULE_STATEMENTS = {
    "RULE_STATEMENTS",
    sizeof(TOKENS_STATEMENTS) / sizeof(TOKENS_STATEMENTS[0]),
    TOKENS_STATEMENTS
};

Token::TType TOKENS_OP[] =
{
    Token::TOKEN_PLUS, Token::TOKEN_MINUS, Token::TOKEN_MULT, Token::TOKEN_DIV, Token::TOKEN_LESSER, Token::TOKEN_GREATER, Token::TOKEN_EQUAL, Token::TOKEN_AND, Token::TOKEN_LER
};
const ParserRule RULE_OP = {
    "RULE_OP",
    sizeof(TOKENS_OP) / sizeof(TOKENS_OP[0]),
    TOKENS_OP
};

Token::TType TOKENS_EXP2[] =
{
    Token::TOKEN_PAREN_L, Token::TOKEN_IDENTIFIER, Token::TOKEN_INTEGER, Token::TOKEN_MINUS, Token::TOKEN_NOT
};
const ParserRule RULE_EXP2 = {
    "RULE_EXP2",
    sizeof(TOKENS_EXP2) / sizeof(TOKENS_EXP2[0]),
    TOKENS_EXP2
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

/*
PROG ::= DECLS STATEMENTS
*/
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

/*
DECLS ::= DECL ; DECLS | 
          <e>
*/
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

/*
DECL ::= int ARRAY identifier
*/
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

/*
STATEMENTS ::= STATEMENT ; STATEMENTS |
               <e>
*/
ParseTree *Parser::parseStatements()
{
    while(RULE_STATEMENTS.isTokenValid(currentToken))
    {
        std::cout << "RULE_STATEMENTS" << std::endl;
        this->parseStatement();
        if(!this->requireToken(Token::TOKEN_SEMICOLON, true))
        {
            throw std::runtime_error("RULE_STATEMENTS: SEMICOLON EXPECTED");
        }
    }
    std::cout << "ENDING RULE_STATEMENTS" << std::endl;
    this->nextToken();
    return this->buildTree(RULE_PROG);
}

/*
STATEMENT ::= identifier INDEX = EXP |
              print ( EXP ) |
              read ( EXP ) |
              { STATEMENTS } |
              if ( EXP ) STATEMENT else STATEMENT |
              while ( EXP ) STATEMENT
*/
ParseTree *Parser::parseStatement()
{
    if(this->requireToken(Token::TOKEN_IDENTIFIER))
    {
        this->nextToken();
        std::cout << "RULE_STATEMENT: IDENTIFIER = EXP;" << std::endl;
        if(requireToken(Token::TOKEN_BRACKET_L))
        {
            this->nextToken();
            this->nextToken();
            this->nextToken();
        }
        requireToken(Token::TOKEN_EQUAL, true);
        this->parseExp();
    }
    else if(this->requireToken(Token::TOKEN_PRINT))
    {
        std::cout << "RULE_STATEMENT: print ( EXP );" << std::endl;
        requireToken(Token::TOKEN_PAREN_L, true);
        this->parseExp();
        requireToken(Token::TOKEN_PAREN_R, true);
    }
    else if(this->requireToken(Token::TOKEN_READ))
    {
        std::cout << "RULE_STATEMENT: read ( EXP );" << std::endl;
        requireToken(Token::TOKEN_PAREN_L, true);
        this->parseExp();
        requireToken(Token::TOKEN_PAREN_R, true);
    }
    else
    {
        throw std::runtime_error("todo...");
    }
    return NULL;
}

/*
EXP ::= EXP2 OP_EXP
*/
ParseTree *Parser::parseExp()
{
    std::cout << "RULE_EXP: TODO!" << std::endl;
    this->parseExp2();
    this->parseOpExp();
    return NULL;
}

/*
EXP2 ::= ( EXP ) |
         identifier INDEX |
         integer |
         - EXP2 |
         ! EXP2
*/
ParseTree *Parser::parseExp2()
{
    if(RULE_EXP2.isTokenValid(currentToken))
    {
        std::cout << "RULE_EXP2 " << currentToken.getTokenDescription() << std::endl;

        if(this->requireToken(Token::TOKEN_INTEGER))
        {
            this->nextToken();
        }
        else if(this->requireToken(Token::TOKEN_IDENTIFIER))
        {
            this->nextToken();
        }
        else
        {
            throw std::runtime_error("EXP2 todo...");
        }
        return NULL;
    }
    throw std::runtime_error("EXP2 did not match!");
}

/*
INDEX ::= [ EXP ] |
          <e>
*/
ParseTree *Parser::parseIndex()
{
    std::cout << "RULE_INDEX: TODO!" << std::endl;
    return NULL;
}

/*
OP_EXP ::= OP EXP |
           <e>
*/
ParseTree *Parser::parseOpExp()
{
    std::cout << "RULE_OPEXP: TODO! " << currentToken.getTokenDescription() << std::endl;
    if(RULE_OP.isTokenValid(currentToken))
    {
        this->parseOp();
    }
    return NULL;
}

/*
OP ::= + | - | * | / | < | > | = | <=> | &
*/
ParseTree *Parser::parseOp()
{
    if(RULE_OP.isTokenValid(currentToken))
    {
        std::cout << "RULE_OP" << std::endl;
        this->nextToken();
        return NULL;
    }
    throw std::runtime_error("todo...");
}
