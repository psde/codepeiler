#ifndef PARSER_HPP
#define PARSER_HPP

#include "Lexer.hpp"
#include "ParseTree.hpp"

class Parser
{
private:

    Lexer *lexer;
    Token currentToken;
    void nextToken();

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
