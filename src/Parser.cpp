//#define PARSER_DEBUG 
#include "Parser.hpp"
#include <iostream>

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
#ifdef PARSER_DEBUG
    std::cout << "Next token is: " << this->currentToken.getTokenDescription() << "@" << this->currentToken.getLine() << "," << this->currentToken.getColumn() << std::endl;
#endif
}

bool Parser::requireToken(Token::TType tok, bool readNext)
{
    bool isOk = false;
    if(currentToken.getType() == tok)
        isOk = true;

#ifdef PARSER_DEBUG
    std::cout << "RequireToken: " << Token::getTokenDescription(tok) << " =? " << currentToken.getTokenDescription() << (readNext ? " - reading next token." : "") << (isOk ? " isOk" : "")  << std::endl;
#endif

    if(isOk && readNext)
        this->nextToken();
    return isOk;
}

bool Parser::requireToken(ParserRule rule, Token::TType tok, bool throwError, bool readNext)
{
    bool isOk = false;
    if(currentToken.getType() == tok)
        isOk = true;

    if(!isOk && throwError)
    {
        String str = "";
        str += Token::getTokenDescription(tok);
        str += " expected.";
        this->throwError(rule, str);
    }

#ifdef PARSER_DEBUG
    std::cout << "RequireToken: " << Token::getTokenDescription(tok) << " =? " << currentToken.getTokenDescription() << (readNext ? " - reading next token." : "") << (isOk ? " isOk" : "")  << std::endl;
#endif

    if(isOk && readNext)
        this->nextToken();
    return isOk;
}

void Parser::throwError(ParserRule rule, String msg)
{
    throw ParserError(currentToken, rule, msg);
}

ParseTree *Parser::parse()
{
#ifdef PARSER_DEBUG
    std::cout << std::endl << "Parsing:" << std::endl;
#endif

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
        Prog *prog = new Prog();
        prog->addDecls(this->parseDecls());
        prog->addStatements(this->parseStatements());
        return prog;
    }
   this->throwError(RULE_PROG);
   return NULL;
}

/*
DECLS ::= DECL ; DECLS | 
          <e>
*/
Decls* Parser::parseDecls()
{
    Decls *decls = new Decls();

    while(RULE_DECLS.isTokenValid(currentToken))
    {
#ifdef PARSER_DEBUG
        std::cout << "RULE_DECLS" << std::endl;
#endif
        decls->addDecl(this->parseDecl());

        this->requireToken(RULE_DECLS, Token::TOKEN_SEMICOLON, true, true);
    }

    return decls;
}

/*
DECL ::= int ARRAY identifier
*/
Decl* Parser::parseDecl()
{
    if(RULE_DECL.isTokenValid(currentToken))
    {
#ifdef PARSER_DEBUG
        std::cout << "RULE_DECL" << std::endl;
#endif

        Decl* decl = new Decl("");
        this->nextToken();

        if(currentToken == Token::TOKEN_IDENTIFIER)
        {
            decl->setIdentifier(currentToken.getLexem());
            this->nextToken();
        }
        else if(currentToken == Token::TOKEN_BRACKET_L)
        {
            this->requireToken(RULE_DECL, Token::TOKEN_BRACKET_L, true, true);
            this->requireToken(RULE_DECL, Token::TOKEN_INTEGER, true);

            decl->setArray(currentToken.getULong());
            this->nextToken();

            this->requireToken(RULE_DECL, Token::TOKEN_BRACKET_R, true, true);
            this->requireToken(RULE_DECL, Token::TOKEN_IDENTIFIER, true);

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
    return NULL;
}

/*
STATEMENTS ::= STATEMENT ; STATEMENTS |
               <e>
*/
Statements* Parser::parseStatements()
{
    Statements* statements = new Statements();
    while(RULE_STATEMENTS.isTokenValid(currentToken))
    {
#ifdef PARSER_DEBUG
        std::cout << "RULE_STATEMENTS" << std::endl;
#endif

        if(this->requireToken(Token::TOKEN_EOF))
            break;

        statements->addStatement(this->parseStatement());

        this->requireToken(RULE_STATEMENTS, Token::TOKEN_SEMICOLON, true, true);
    }
    return statements;
}

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
#ifdef PARSER_DEBUG
        std::cout << "RULE_STATEMENT: IDENTIFIER INDEX = EXP;" << std::endl;
#endif

        Statement_1 *statement = new Statement_1();
        statement->setIdentifier(currentToken.getLexem());
        this->nextToken();
        statement->setIndex(this->parseIndex());
        this->requireToken(RULE_STATEMENT, Token::TOKEN_EQUAL, true, true);
        statement->setExp(this->parseExp());
        return statement;
    }
    else if(this->requireToken(Token::TOKEN_PRINT))
    {
#ifdef PARSER_DEBUG
        std::cout << "RULE_STATEMENT: print ( EXP );" << std::endl;
#endif

        Statement_2 *statement = new Statement_2();
        this->nextToken();
        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_L, true, true);
        statement->setExp(this->parseExp());
        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_R, true, true);
        return statement;
    }
    else if(this->requireToken(Token::TOKEN_READ))
    {
        this->nextToken();
#ifdef PARSER_DEBUG
        std::cout << "RULE_STATEMENT: read ( EXP );" << std::endl;
#endif

        Statement_3 *statement = new Statement_3();
        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_L, true, true);
        statement->setExp(this->parseExp());
        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_R, true, true);
        return statement;
    }
    else if(this->requireToken(Token::TOKEN_BRACE_L))
    {
        this->nextToken();
#ifdef PARSER_DEBUG
        std::cout << "RULE_STATEMENT: { STATEMENTS }" << std::endl;
#endif

        Statement_4 *statement = new Statement_4();
        statement->setStatements(this->parseStatements());
        this->requireToken(RULE_STATEMENT, Token::TOKEN_BRACE_R, true, true);
        return statement;
    }
    else if(this->requireToken(Token::TOKEN_IF))
    {
        this->nextToken();
#ifdef PARSER_DEBUG
        std::cout << "RULE_STATEMENT: IF ( EXP ) STATEMENT else STATEMENT" << std::endl;
#endif

        Statement_5 *statement = new Statement_5();
        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_L, true, true);
        statement->setExp(this->parseExp());
        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_R, true, true);
        statement->setStatement1(this->parseStatement());

        if(this->requireToken(Token::TOKEN_ELSE))
        {
            this->nextToken();
            statement->setStatement2(this->parseStatement());
        }
        return statement;
    }
    else if(this->requireToken(Token::TOKEN_WHILE))
    {
        this->nextToken();
       
#ifdef PARSER_DEBUG
        std::cout << "RULE_STATEMENT: while ( EXP ) statement" << std::endl;
#endif

        Statement_6 *statement = new Statement_6();

        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_L, true, true);
        statement->setExp(this->parseExp());
        this->requireToken(RULE_STATEMENT, Token::TOKEN_PAREN_R, true, true);
        statement->setStatement(this->parseStatement());
        return statement;
    }
    else
    {
        this->throwError(RULE_STATEMENT, "RULE_STATEMENT Not implemented.");
    }
    this->throwError(RULE_STATEMENT);
    return NULL;
}

/*
EXP ::= EXP2 OP_EXP
*/
Exp* Parser::parseExp()
{
#ifdef PARSER_DEBUG
    std::cout << "RULE_EXP ::= EXP2 OP_EXP" << std::endl;
#endif

    Exp *exp = new Exp();
    exp->addExp2(this->parseExp2());
    exp->addOpExp(this->parseOpExp());
    return exp;
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
    if(RULE_EXP2.isTokenValid(currentToken))
    {
#ifdef PARSER_DEBUG
        std::cout << "RULE_EXP2" << std::endl;
#endif

        if(this->requireToken(Token::TOKEN_PAREN_L))
        {
            Exp2_1 *exp2 = new Exp2_1();
            this->nextToken();
            exp2->setExp(this->parseExp());
            this->nextToken();
            return exp2;
        }
        else if(this->requireToken(Token::TOKEN_IDENTIFIER))
        {
            Exp2_2 *exp2 = new Exp2_2();
            exp2->setIdentifier(currentToken.getLexem());
            this->nextToken();
            exp2->setIndex(this->parseIndex());
            return exp2;
        }
        else if(this->requireToken(Token::TOKEN_INTEGER))
        {
            Exp2_3 *exp2 = new Exp2_3();
            exp2->setInteger(currentToken.getULong());
            this->nextToken();
            return exp2;
        }
        else if(this->requireToken(Token::TOKEN_MINUS))
        {
            Exp2_4 *exp2 = new Exp2_4();
            this->nextToken();
            exp2->setExp2(this->parseExp2());
            return exp2;
        }
        else if(this->requireToken(Token::TOKEN_NOT))
        {
            Exp2_5 *exp2 = new Exp2_5();
            this->nextToken();
            exp2->setExp2(this->parseExp2());
            return exp2;
        }
        else
        {
            this->throwError(RULE_EXP2, "RULE_EXP2 Not implemented.");
        }
    }
    this->throwError(RULE_EXP2);
    return NULL;
}

/*
INDEX ::= [ EXP ] |
          <e>
*/
Index* Parser::parseIndex()
{
#ifdef PARSER_DEBUG
    std::cout << "RULE_INDEX" << std::endl;
#endif

    Index *index = new Index();
    if(this->requireToken(Token::TOKEN_BRACKET_L))
    {
        this->nextToken();
        index->setExp(this->parseExp());
        this->nextToken();
    }
    return index;
}

/*
OP_EXP ::= OP EXP |
           <e>
*/
OpExp* Parser::parseOpExp()
{
    OpExp *opexp = new OpExp();
    if(RULE_OP.isTokenValid(currentToken))
    {
#ifdef PARSER_DEBUG
        std::cout << "RULE_OPEXP" << std::endl;
#endif
        opexp->setOp(this->parseOp());
        opexp->setExp(this->parseExp());
    }
    return opexp;
}

/*
OP ::= + | - | * | / | < | > | = | <=> | &
*/
Op* Parser::parseOp()
{
    if(RULE_OP.isTokenValid(currentToken))
    {
#ifdef PARSER_DEBUG
        std::cout << "RULE_OP" << std::endl;
#endif

        Op::OpType type;
        switch(currentToken.getType())
        {
            case Token::TOKEN_PLUS:
                type = Op::OP_PLUS; break;
            case Token::TOKEN_MINUS:
                type = Op::OP_MINUS; break;
            case Token::TOKEN_MULT:
                type = Op::OP_MULT; break;
            case Token::TOKEN_DIV:
                type = Op::OP_DIV; break;
            case Token::TOKEN_LESSER:
                type = Op::OP_LESSER; break;
            case Token::TOKEN_GREATER:
                type = Op::OP_GREATER; break;
            case Token::TOKEN_EQUAL:
                type = Op::OP_EQUAL; break;
            case Token::TOKEN_LER:
                type = Op::OP_LER; break;
            case Token::TOKEN_AND:
                type = Op::OP_AND; break;
            default:
                throw ParserRule(RULE_OP);
        };

        Op *op = new Op(type);
        this->nextToken();
        return op;
    }
    throw ParserRule(RULE_OP);
    return NULL;
}
