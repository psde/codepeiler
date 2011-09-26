#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include "ParserRule.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "String.hpp"
#include "Vector.hpp"

class ParseTree
{
protected:

public:
    //virtual void makeCode() = 0;
};

class IdentifierParseTree : public ParseTree
{
protected:
    String identifier;

public:
    IdentifierParseTree(String identifier)
     : identifier(identifier) {}

    String getIdentifier() { return this->identifier; }
    void setIdentifier(String identifier) { this->identifier = identifier; }
};

class Decl : public IdentifierParseTree
{
protected:
    bool array;
    int arraySize;

public:
    Decl(String identifier)
     : IdentifierParseTree(identifier) {}

    bool getArray() { return this->array; }
    int getArraySize() { return this->arraySize; }
    void setArray(int size) { this->array = true; this->arraySize = size; }
};

class Decls : public ParseTree
{
protected:
    Vector<Decl*> *decls;

public:
    Decls() { this->decls = new Vector<Decl*>(); }

    ~Decls() { delete this->decls; }
  
    void addDecl(Decl *decl) { this->decls->append(decl); }
    Vector<Decl*>* getDecls() { return this->decls; }
};

class Op : public ParseTree
{

};

class OpExp : public ParseTree
{

};

class Index : public ParseTree
{

};

class Exp2 : public ParseTree
{

};

class Exp : public ParseTree
{
protected:
    Exp2* exp2;
    OpExp* opexp;

public:
    Exp() {}
    ~Exp() { delete this->exp2; delete this->opexp; }

    void addExp2(Exp2 *exp2) { this->exp2 = exp2; }
    Exp2* getExp2() { return this->exp2; }

    void addOpExp(OpExp *opexp) { this->opexp = opexp; }
    OpExp* getOpExp() { return this->opexp; }
};

class Statement : public ParseTree
{

};

class Statements : public ParseTree
{
protected:
    Vector<Statement*> *statements;
public:
    Statements() { this->statements = new Vector<Statement*>(); }

    ~Statements() { delete this->statements;  }

    void addStatement(Statement *statement) { this->statements->append(statement); }
    Vector<Statement*>* getStatements() { return this->statements; }
};

class Prog : public ParseTree 
{
protected:
    Decls *decls;
    Statements *statements;

public:
    Prog() {}
    ~Prog() { delete this->decls; delete this->statements; }

    void addDecls(Decls *decls) { this->decls = decls; }
    Decls* getDecls() { return this->decls; }

    void addStatements(Statements *statements) { this->statements = statements; }
    Statements* getStatements() { return this->statements; }
};


/*
class ParseTreeLeaf;

enum Type
{
    TYPE_ERROR = -1,
    TYPE_NONE,
    TYPE_INT
};

enum Operand
{
    OP_NONE = 0,
    OP_PLUS,
    OP_MINUS,
    OP_MULT,
    OP_DIV,
    OP_LESSER,
    OP_GREATER,
    OP_EQUAL,
    OP_AND
};


class ParseTree
{
private:
    ParserRule rule;

protected:
    Position pos;
    int nodeCount;
    ParseTree *nodes[3];

    Type type;
    Operand op;

public:
    ParseTree(ParserRule rule, int line, int column)
     : rule(rule), pos(line, column, 0), nodeCount(0), type(TYPE_NONE), op(OP_NONE)
    {
        for(int i=0; i<3; i++)
            this->nodes[i] = NULL;
    }

    void addNode(ParseTree *node)
    {
        if(this->nodeCount >= 3)
            throw std::runtime_error("ParseTree::addNode() - nodeCount >= 3");

        this->nodes[this->nodeCount++] = node;
    }

    ParseTree* getNode(int index)
    {
        if(index >= 3)
            throw std::runtime_error("ParseTree::getNode() - index >= 3");

        return this->nodes[index];
    }

    ParseTreeLeaf* getLeaf(int index)
    {
        return (ParseTreeLeaf*)this->getNode(index);
    }

    int getNodeCount() { return this->nodeCount; }
    ParserRule getRule() { return this->rule; }
    Position getPosition() { return this->pos; }

    void setOp(Operand op) { this->op = op; }
    Operand getOp() { return this->op; }

    void setType(Type type) { this->type = type; }
    Type getType() { return this->type; }
};

class ParseTreeLeaf : public ParseTree
{
private:
    bool array;
    int arraySize;

    Token tok;

public:
    ParseTreeLeaf(Token tok)
     : ParseTree(RULE_NONE, tok.getLine(), tok.getColumn())
    {
        this->tok = tok;
    }

    void setArray(int size = 0) { this->array = true; this->arraySize = size; }
    bool isArray() { return this->array; }

    void setToken(Token tok)
    {
        this->tok = tok;
        this->pos = Position(tok.getLine(), tok.getColumn());
    }
    Token getToken() { return this->tok; }
};
*/

#endif
