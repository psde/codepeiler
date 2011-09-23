#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include "ParseRule.hpp"
#include "Token.hpp"

class ParseTreeLeaf;

class ParseTree
{
private:
    ParserRule rule;
    int line;
    int column;

public:
    ParseTree(ParserRule rule, int line, int column)
     : rule(rule), line(line), column(column)
    {

    }

    void addNode(ParseTree *node)
    {

    }

    ParseTree* getNode(int index);
    ParseTreeLeaf* getLeaf(int index);

    int getNodeCount();
    ParserRule getRule();
    int getLine();
    int getColumn();


};

class ParseTreeLeaf : public ParseTree
{
private:

public:

};

#endif
