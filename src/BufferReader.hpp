#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

class BufferReader
{
private:
    static const int BUFFER_SIZE = 1024 * 4;
    int fileDescriptor;
    ssize_t fileLength;
    ssize_t filePosition;
    char* fileBuffer;

    ssize_t bufferPosition;

public:
    
    BufferReader(const char* file)
    {
        this->fileDescriptor = open(file, O_DIRECT);
        this->fileLength = lseek(this->fileDescriptor, 0, SEEK_END);
        lseek(this->fileDescriptor, 0, SEEK_SET);
        this->bufferPosition = 0;

        // Allocate aligned space for buffer
        this->fileBuffer = (char*)valloc(BufferReader::BUFFER_SIZE);

        this->filePosition = read(this->fileDescriptor, this->fileBuffer, BufferReader::BUFFER_SIZE / 2);

        // Reading failed
        if(this->filePosition != BufferReader::BUFFER_SIZE / 2 && this->filePosition != this->fileLength)
            throw "Error while reading from File";
        
    }

    ~BufferReader()
    {
        free(this->fileBuffer);
    }

    // Peeks the next char in buffer
    unsigned char peekChar()
    {
        unsigned char peek = this->getChar();
        this->ungetChar(1);
        return peek;
    }

    // Gets next char in buffer
    unsigned char getChar()
    {
        int position = this->bufferPosition++;
        
        if(position >= this->fileLength)
        {
            return 0x00;
        }

        if(this->bufferPosition > this->filePosition )
        {
            ssize_t bytesToRead = BufferReader::BUFFER_SIZE / 2;

            ssize_t bytesRead = read(this->fileDescriptor, this->fileBuffer + this->filePosition % BufferReader::BUFFER_SIZE, bytesToRead);
            /*if(bytesRead != bytesToRead)
            {
                std::cout << "shit man" << std::endl;
                throw "Unrecoverable error while Buffer::getChar()";
            }
            else*/
            {
                this->filePosition += bytesRead;
            }
        }

        return this->fileBuffer[position % BufferReader::BUFFER_SIZE];
    }

    // Set the buffer position back
    void ungetChar(int count)
    {
        if(count < 0) 
            count = 0;

        if(this->bufferPosition - count < 0)
            count = this->bufferPosition;

        this->bufferPosition -= count;
    }

};

#endif
