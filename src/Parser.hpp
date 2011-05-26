#ifndef PARSER_HPP
#define PARSER_HPP

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

    /*enum RuleTypes {
        RULE_PROGSTART = 0,
        RULE_NO
    };
    List<Token::TType> rules[Parser::RULE_NO];*/

    Lexer *lexer;
    Token currentToken;
    void nextToken();

    bool isTokenInRule(Token tok, Token::TType *rule, int size);
    void setup();

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
