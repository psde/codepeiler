#include <iostream>

#include "buffer.hpp"
#include "lexer.hpp"

int main(int argc, char *argv[])
{
    Buffer *buf = new Buffer("lexer_test.txt");
    Lexer *lex = new Lexer(buf);

    bool loop = true;

    while(loop)
    {
        Token token = lex->nextToken();
        
        std::cout << "token: " << (int)token.type() << std::endl;

        if(token.type() == Token::TOKEN_EOF)
            loop = false;
    }

    std::cout << "done" << std::endl;
	return 0;
}
