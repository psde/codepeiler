#ifndef PARSER_HPP
#define PARSER_HPP

#include "Token.hpp"
#include "Lexer.hpp"
#include "ParseTree.hpp"
#include "List.hpp"
#include "Token.hpp"

struct Rule {
    int size;
    Token::TType* tokens;

    bool isTokenValid(Token tok) const {
        for(int i=0; i<size; i++)
            if(tok.getType() == tokens[i])
                return true; 
        return false;
    }   
};  

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
