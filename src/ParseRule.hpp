#ifndef PARSERULE_HPP
#define PARSERULE_HPP

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


#endif
