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
    static const int BUFFER_SIZE = 1024 * 4;
    int fileDescriptor;
    ssize_t fileLength;
    ssize_t filePosition;
    char* fileBuffer;

    ssize_t bufferPosition;

public:
    
    Buffer(const char* file)
    {
        this->fileDescriptor = open(file, O_DIRECT);
        this->fileLength = lseek(this->fileDescriptor, 0, SEEK_END);
        lseek(this->fileDescriptor, 0, SEEK_SET);
        this->bufferPosition = 0;

		// Allocate aligned space for buffer
        this->fileBuffer = (char*)valloc(Buffer::BUFFER_SIZE);

        this->filePosition = read(this->fileDescriptor, this->fileBuffer, Buffer::BUFFER_SIZE / 2);

		// Reading failed
		if(this->filePosition != Buffer::BUFFER_SIZE / 2)
		{
			exit(-1);
			//TODO: Exception?
		}
        
    }

    ~Buffer()
    {
        free(this->fileBuffer);
    }

	// Gets next char in buffer
    unsigned char getChar()
    {
        int position = this->bufferPosition++;


        if(this->bufferPosition > this->filePosition )
        {
            ssize_t bytesRead = read(this->fileDescriptor, this->fileBuffer + this->filePosition % Buffer::BUFFER_SIZE, Buffer::BUFFER_SIZE / 2);
            if(bytesRead != Buffer::BUFFER_SIZE / 2)
            {
                // TODO: error handling
            }
            else
            {
                this->filePosition += bytesRead;
            }
        }

        return this->fileBuffer[position % Buffer::BUFFER_SIZE];
    }

	// Set the buffer position back
    void ungetChar(int count)
    {
        this->bufferPosition -= count;
    }

};

#endif
