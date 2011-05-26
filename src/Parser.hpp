#ifndef PARSER_HPP
#define PARSER_HPP

#include "ParseRule.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "ParseTree.hpp"
#include "List.hpp"
#include "Token.hpp"
#include "String.hpp"
#include "ParseRule.hpp"

class Parser
{
private:

    Lexer *lexer;
    Token currentToken;
    void nextToken();

    ParseTree *buildTree(ParseRule rule);

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
