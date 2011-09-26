#include "Parser.hpp"

#include <iostream>

Parser::Parser(Lexer *lexer)
 : lexer(lexer)
{

}

Parser::~Parser()
{

}

ParseTree *Parser::buildTree(ParserRule rule)
{
    return NULL; 
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

    //std::cout << "RequireToken: " << Token::getTokenDescription(tok) << " =? " << currentToken.getTokenDescription() << (readNext ? " - reading next token." : "") << (isOk ? " isOk" : "")  << std::endl;

    if(readNext)
        this->nextToken();
    return isOk;
}

void Parser::throwError(ParserRule rule, String msg)
{
    throw ParserError(currentToken, rule, msg);
}

ParseTree *Parser::parse()
{
    std::cout << std::endl << "Parsing:" << std::endl;
    this->nextToken();
    return this->parseProg();
}

/*
PROG ::= DECLS STATEMENTS
*/
Prog* Parser::parseProg()
{
    if(RULE_PROG.isTokenValid(currentToken))
    {
        std::cout << "RULE_PROG" << std::endl;
        Prog *prog = new Prog();
        prog->addDecls(this->parseDecls());
        prog->addStatements(this->parseStatements());
        return prog;
    }
   this->throwError(RULE_PROG); 
}
/*
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
   this->throwError(RULE_PROG); 
}
*/

/*
DECLS ::= DECL ; DECLS | 
          <e>
*/
Decls* Parser::parseDecls()
{
    Decls *decls = new Decls();

    while(RULE_DECLS.isTokenValid(currentToken))
    {
        std::cout << "RULE_DECLS" << std::endl;

        decls->addDecl(this->parseDecl());

        if(!this->requireToken(Token::TOKEN_SEMICOLON, true))
            this->throwError(RULE_DECL, "TOKEN_SEMICOLON expected.");
    }

    return decls;
}
/*
ParseTree *Parser::parseDecls()
{
    ParseTree *top = NULL;
    ParseTree *prev = NULL;

    while(RULE_DECLS.isTokenValid(currentToken))
    {
        std::cout << "RULE_DECLS" << std::endl;

        ParseTree *tree = this->buildTree(RULE_DECLS);
        
        if(top == NULL)
            top = tree;

        tree->addNode(this->parseDecl());

        if(prev != NULL)
            prev->addNode(tree);
        prev = tree;
       
        if(!this->requireToken(Token::TOKEN_SEMICOLON, true))
            this->throwError(RULE_DECL, "TOKEN_SEMICOLON expected.");
    }
    
    return top;
}
*/

/*
DECL ::= int ARRAY identifier
*/
Decl* Parser::parseDecl()
{
    if(RULE_DECL.isTokenValid(currentToken))
    {
        std::cout << "RULE_DECL" << std::endl;
        Decl* decl = new Decl("");
        this->nextToken();

        if(currentToken == Token::TOKEN_IDENTIFIER)
        {
            decl->setIdentifier(currentToken.getLexem());
            this->nextToken();
        }
        else if(currentToken == Token::TOKEN_BRACKET_L)
        {
            if(!requireToken(Token::TOKEN_BRACKET_L, true))
                this->throwError(RULE_DECL, "TOKEN_BRACKET_L expected.");
            
            if(!requireToken(Token::TOKEN_INTEGER))
                this->throwError(RULE_DECL, "TOKEN_INTEGER expected.");

            decl->setArray(currentToken.getULong());
            this->nextToken();

            if(!requireToken(Token::TOKEN_BRACKET_R, true))
                this->throwError(RULE_DECL, "TOKEN_BRACKET_R expected.");
           
            if(!requireToken(Token::TOKEN_IDENTIFIER))
                this->throwError(RULE_DECL, "TOKEN_IDENTIFIER expected.");

            decl->setIdentifier(currentToken.getLexem());
            this->nextToken();
        }
        else
        {
            this->throwError(RULE_DECL);
        }

        return decl;

    }
    this->throwError(RULE_DECL);
}
/*
ParseTree *Parser::parseDecl()
{
    if(RULE_DECL.isTokenValid(currentToken))
    {
        std::cout << "RULE_DECL" << std::endl;

        ParseTree *tree = this->buildTree(RULE_DECL);
        tree->addNode(this->buildTree(RULE_TYPE_INT));
        this->nextToken();
       
        ParseTreeLeaf *leaf;
        // Identifier?
        if(currentToken.getType() == Token::TOKEN_IDENTIFIER)
        {
            leaf = new ParseTreeLeaf(currentToken);
            this->nextToken();
        }
        // Array?
        else if(currentToken.getType() == Token::TOKEN_BRACKET_L)
        {

            leaf = new ParseTreeLeaf(currentToken);
            if(!requireToken(Token::TOKEN_BRACKET_L, true))
                this->throwError(RULE_DECL, "TOKEN_BRACKET_L expected.");
            
            if(!requireToken(Token::TOKEN_INTEGER))
                this->throwError(RULE_DECL, "TOKEN_INTEGER expected.");

            leaf->setArray(currentToken.getULong());
            this->nextToken();

            if(!requireToken(Token::TOKEN_BRACKET_R, true))
                this->throwError(RULE_DECL, "TOKEN_BRACKET_R expected.");
           
            if(!requireToken(Token::TOKEN_IDENTIFIER))
                this->throwError(RULE_DECL, "TOKEN_IDENTIFIER expected.");

            leaf->setToken(currentToken);
            this->nextToken();
        }
        else
        {
            this->throwError(RULE_DECL, "Not implemented yet");
        }

        return tree;
    }
    this->throwError(RULE_DECL);
}
*/

/*
STATEMENTS ::= STATEMENT ; STATEMENTS |
               <e>
*/
Statements* Parser::parseStatements()
{
    Statements* statements = new Statements();
    while(RULE_STATEMENTS.isTokenValid(currentToken))
    {
        std::cout << "RULE_STATEMENTS" << std::endl;

        statements->addStatement(this->parseStatement());

        if(!this->requireToken(Token::TOKEN_SEMICOLON, true))
            this->throwError(RULE_STATEMENTS, "TOKEN_SEMICOLON expected.");
    }
    this->nextToken();
    return statements;
}
/*
   ParseTree *Parser::parseStatements()
{
    ParseTree *top = NULL;
    ParseTree *prev = NULL;
    
    while(RULE_STATEMENTS.isTokenValid(currentToken))
    {
        std::cout << "RULE_STATEMENTS" << std::endl;
        ParseTree *tree = this->buildTree(RULE_STATEMENTS);

        if(top == NULL)
            top = tree;

        tree->addNode(this->parseStatement());

        if(prev)
            prev->addNode(tree);
        prev = tree;

        if(!this->requireToken(Token::TOKEN_SEMICOLON, true))
        {
            this->throwError(RULE_STATEMENTS, "TOKEN_SEMICOLON expected.");
        }
    }
    this->nextToken();
    return this->buildTree(RULE_PROG);
}
*/

/*
STATEMENT ::= identifier INDEX = EXP |
              print ( EXP ) |
              read ( EXP ) |
              { STATEMENTS } |
              if ( EXP ) STATEMENT else STATEMENT |
              while ( EXP ) STATEMENT
*/
Statement* Parser::parseStatement()
{
    if(this->requireToken(Token::TOKEN_IDENTIFIER))
    {
        this->nextToken();
        std::cout << "RULE_STATEMENT: IDENTIFIER INDEX = EXP;" << std::endl;
        this->parseIndex();
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
        this->throwError(RULE_STATEMENT, "Not implemented.");
    }
    return NULL;

}

/*
EXP ::= EXP2 OP_EXP
*/
Exp* Parser::parseExp()
{
    Exp *exp = new Exp();
    exp->addExp2(this->parseExp2());
    exp->addOpExp(this->parseOpExp());
    return NULL;
}

/*
EXP2 ::= ( EXP ) |
         identifier INDEX |
         integer |
         - EXP2 |
         ! EXP2
*/
Exp2* Parser::parseExp2()
{
    return NULL;
}
/*
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
            this->parseIndex();
        }
        else
        {
            this->throwError(RULE_EXP2, "Not implemented.");
        }
        return NULL;
    }
    this->throwError(RULE_EXP2);
}
*/

/*
INDEX ::= [ EXP ] |
          <e>
*/
Index* Parser::parseIndex()
{
    return NULL;
}
/*
ParseTree *Parser::parseIndex()
{
    std::cout << "RULE_INDEX: TODO!" << std::endl;
    if(this->requireToken(Token::TOKEN_BRACKET_L))
    {
        this->nextToken();
        this->parseExp();
        this->nextToken();
    }
    return NULL;
}
*/

/*
OP_EXP ::= OP EXP |
           <e>
*/
OpExp* Parser::parseOpExp()
{
    return NULL;
}
/*
ParseTree *Parser::parseOpExp()
{
    std::cout << "RULE_OPEXP: TODO! " << currentToken.getTokenDescription() << std::endl;
    if(RULE_OP.isTokenValid(currentToken))
    {
        this->parseOp();
        this->parseExp();
    }
    return NULL;
}
*/

/*
OP ::= + | - | * | / | < | > | = | <=> | &
*/
Op* Parser::parseOp()
{
    return NULL;
}
/*
ParseTree *Parser::parseOp()
{
    if(RULE_OP.isTokenValid(currentToken))
    {
        std::cout << "RULE_OP" << std::endl;
        this->nextToken();
        return NULL;
    }
    throw ParserRule(RULE_OP);
}
*/
