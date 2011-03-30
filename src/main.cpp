#include <iostream>

#include "buffer.hpp"
#include "lexer.hpp"

int main(int argc, char *argv[])
{
    Buffer *buf = new Buffer("lexer_test.txt");
    Lexer *lex = new Lexer(buf);


    std::cout << "done" << std::endl;
	return 0;
}
