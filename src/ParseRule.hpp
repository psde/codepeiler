#ifndef PARSERULE_HPP
#define PARSERULE_HPP

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
