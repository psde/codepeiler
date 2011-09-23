#ifndef PARSER_HPP
#define PARSER_HPP

#include "ParserRule.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "ParseTree.hpp"
#include "List.hpp"
#include "Token.hpp"
#include "String.hpp"

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
