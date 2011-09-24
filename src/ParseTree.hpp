#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include "ParserRule.hpp"
#include "Token.hpp"
#include "Lexer.hpp"

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
    Position pos;

protected:
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
    ParseTreeLeaf(Token tok, int line, int column)
     : ParseTree(RULE_NONE, line, column)
    {
        this->tok = tok;
    }

    void setArray(int size = 0) { this->array = true; this->arraySize = size; }
    bool isArray() { return this->array; }
    Token getToken() { return this->tok; }
};

#endif
