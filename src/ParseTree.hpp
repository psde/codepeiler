#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include "ParseRule.hpp"
#include "Token.hpp"

struct ParserRule;

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

};

#endif
