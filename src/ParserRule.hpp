#ifndef PARSERRULE_HPP
#define PARSERRULE_HPP

#include "String.hpp"
#include "Token.hpp"

struct ParserRule {
    String name;
    int size;
    Token::TType* tokens;

    bool isTokenValid(Token tok) const {
        for(int i=0; i<size; i++)
            if(tok.getType() == tokens[i])
                return true; 
        return false;
    }  
};  

extern const ParserRule RULE_NONE;
extern const ParserRule RULE_PROG;
extern const ParserRule RULE_DECLS;
extern const ParserRule RULE_DECL;
extern const ParserRule RULE_TYPE_INT;
extern const ParserRule RULE_STATEMENT;
extern const ParserRule RULE_STATEMENTS;
extern const ParserRule RULE_OP;
extern const ParserRule RULE_EXP2;

/*
template<typename T>
struct newParserRule {
    const char* name;
    std::size_t size;
    T* v;

    template<typename... Args>
    newParserRule(const char* name, Args... tokens)
     : name(name), size(sizeof...(tokens)),
       v(new T[sizeof...(tokens)] { tokens... })
    {}

    ~newParserRule() {
        delete[] v;
    }
};

const newParserRule<Token::TType> ary("derp", Token::TOKEN_INT);
*/
#endif
