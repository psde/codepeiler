#include <iostream>
#include <iomanip>

#include "buffer.hpp"
#include "lexer.hpp"

int main(int argc, char *argv[])
{
    Buffer *buf = new Buffer("lexer_test.txt");
    Lexer *lex = new Lexer(buf);

    bool loop = true;
    
    std::cout << std::endl << "staring lexical analysis" << std::endl << std::endl;
    std::cout << std::setiosflags(std::ios::left) << std::setw(6) << "line" << std::setw(8) << "column" << std::setw(7) << "TType" << std::setw(20) << "token" << std::setw(16) << "lexem" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    while(loop)
    {
        Token token = lex->nextToken();
        
        std::cout << std::setw(6) << token.line() << std::setw(8) << token.column() << std::setw(7) << (int)token.type() << std::setw(20) << token.echo() << std::setw(16) << token.lexem() << std::endl;
        //std::cout << "token: " << token.echo() << " (" << (int)token.type() << ") l: " << token.line() << " c: " << token.column() << std::endl;

        if(token.type() == Token::TOKEN_EOF)
            loop = false;
    }

    std::cout << std::endl << "done" << std::endl;
	return 0;
}
