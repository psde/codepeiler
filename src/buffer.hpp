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
		if(this->filePosition != Buffer::BUFFER_SIZE / 2 && this->filePosition != this->fileLength)
		{
            std::cout << this->filePosition << std::endl;
			//exit(-1);
			// TODO: Exception?
		}
        
    }

    ~Buffer()
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
            return 0x04;
        }

        if(this->bufferPosition > this->filePosition )
        {
            ssize_t bytesToRead = Buffer::BUFFER_SIZE / 2;

            // TODO: This doesn't work.
            // check if bytesToRead exceeds the file length
            /*if(this->filePosition + bytesToRead > this->fileLength)
            {
                bytesToRead = this->fileLength - this->filePosition;
            }*/

            ssize_t bytesRead = read(this->fileDescriptor, this->fileBuffer + this->filePosition % Buffer::BUFFER_SIZE, bytesToRead);
            if(bytesRead != bytesToRead)
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
        if(count < 0) 
            count = 0;

        if(this->bufferPosition - count < 0)
            count = this->bufferPosition;

        this->bufferPosition -= count;
    }

};

#endif
