#include <iostream>

#include "buffer.hpp"

int main(int argc, char *argv[])
{
	std::cout << "asd" << std::endl;

    Buffer *buf = new Buffer("test.txt");

    std::cout << std::endl;

    for(int i=0; i<520;i++)
        std::cout << buf->getChar();

    std::cout << std::endl;

    buf->ungetChar(20);
    
    for(int i=0; i<100; i++)
        std::cout << buf->getChar();
    
    std::cout << std::endl;    

	return 0;
}
