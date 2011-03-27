#include <iostream>

#include "buffer.hpp"

int main(int argc, char *argv[])
{
	std::cout << "asd" << std::endl;

    Buffer *buf = new Buffer("test.txt");

    for(int i=0; i<1024*2;i++)
        std::cout << buf->getChar();
    
    
    std::cout << std::endl;    

	return 0;
}
