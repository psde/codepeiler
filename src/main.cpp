#include <iostream>
#include <iomanip>

#include "string.hpp"
#include "buffer.hpp"
#include "lexer.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << "usage: \tcodepeiler input [output]" << std::endl;
        std::cout << "\t\tinput: source code file to be analysed." << std::endl;
        std::cout << "\t\toutput: optional, will write output to. stdout is used by default." << std::endl;
        return 0;
    }

    String output = "";

    if(argc == 3)
    {
        output = argv[2];
    }

    Buffer *buf = new Buffer(argv[1]);
    Lexer *lex = new Lexer(buf);

    if(output == "")
    {
        std::cout << std::setiosflags(std::ios::left) << std::endl;
        std::cout << "  " << std::setw(6) << "line" << std::setw(8) << "column" << std::setw(20) << "token" << std::setw(16) << "lexem" << std::endl;
        std::cout << "  --------------------------------------------------------" << std::endl;
    }

    Token token;
    while(true)
    {
        token = lex->nextToken();
        
        if(output == "")
        {
            std::cout << "  " << std::setw(6) << token.line() << std::setw(8) << token.column() << std::setw(20) << token.echo() << std::setw(16) << token.lexem();
            if(token.type() == Token::TOKEN_INTEGER)
                std::cout << " Value: " << token.lexem().toULong();
            std::cout << std::endl;
        }
        else
        {

        }
         
        if(token.type() == Token::TOKEN_EOF)
            break;
    }

    return 0;

    /*
    Buffer *buf = new Buffer("lexer_test.txt");
    Lexer *lex = new Lexer(buf);

    bool loop = true;
    
    std::cout << std::endl << "starting lexical analysis" << std::endl << std::endl;
    std::cout << "  " << std::setiosflags(std::ios::left) << std::setw(6) << "line" << std::setw(8) << "column" << std::setw(7) << "TType" << std::setw(20) << "token" << std::setw(16) << "lexem" << std::endl;
    std::cout << "  --------------------------------------------------------" << std::endl;
    while(loop)
    {
        Token token = lex->nextToken();
        
        std::cout << "  " << std::setw(6) << token.line() << std::setw(8) << token.column() << std::setw(7) << (int)token.type() << std::setw(20) << token.echo() << std::setw(16) << token.lexem();
        if(token.type() == Token::TOKEN_INTEGER)
            std::cout << " Value: " << token.lexem().toULong();
        std::cout << std::endl;
        //std::cout << "token: " << token.echo() << " (" << (int)token.type() << ") l: " << token.line() << " c: " << token.column() << std::endl;

        if(token.type() == Token::TOKEN_EOF)
            loop = false;
    }

    std::cout << std::endl << "done" << std::endl;
	return 0;*/
}
