#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

class Buffer
{
private:
    // 4kb buffer
    static const int BUFFER_SIZE = 4096;
    int fileDescriptor;
    int fileLength;
    char* fileBuffer;

    int bufferPosition;

public:
    
    Buffer(const char* file)
    {
        this->fileDescriptor = open(file, O_DIRECT);
        this->fileLength = lseek(this->fileDescriptor, 0, SEEK_END);
        lseek(this->fileDescriptor, 0, SEEK_SET);
        this->bufferPosition = 0;
        this->fileBuffer = (char*)valloc(Buffer::BUFFER_SIZE);

        read(this->fileDescriptor, this->fileBuffer, Buffer::BUFFER_SIZE / 2);
    }

    ~Buffer()
    {
        free(this->fileBuffer);
    }

    char getChar()
    {
        int oldPosition = this->bufferPosition++;

        if(bufferPosition == 0)
        {
            read(this->fileDescriptor, this->fileBuffer, Buffer::BUFFER_SIZE / 2);
        }
        else if(bufferPosition == Buffer::BUFFER_SIZE / 2)
        {
            read(this->fileDescriptor, this->fileBuffer + Buffer::BUFFER_SIZE / 2, Buffer::BUFFER_SIZE / 2);
        }

        return this->fileBuffer[oldPosition % Buffer::BUFFER_SIZE];
    }

    void ungetChar(int count)
    {
        this->bufferPosition -= count;
    }

};

#endif
