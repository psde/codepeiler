#ifndef BUFFERWRITER_HPP
#define BUFFERWRITER_HPP

#include <errno.h>
#include "String.hpp"

class BufferWriter
{
private:
    static const int BUFFER_SIZE = 1024 * 4;
    
    int fileDescriptor;
    char* writeBuffer;
    int bufferPosition;

    void addToBuffer(char c)
    {
        this->writeBuffer[bufferPosition++] = c;

        if(this->bufferPosition > BufferWriter::BUFFER_SIZE)
            this->flush();
    }

public:

    BufferWriter(const char* file)
    {
        this->fileDescriptor = open(file, O_DIRECT | O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);

        this->writeBuffer = (char*)valloc(BufferWriter::BUFFER_SIZE);
        memset(this->writeBuffer, 0, BufferWriter::BUFFER_SIZE);

        this->bufferPosition = 0;
    }

    ~BufferWriter()
    {
        this->flush();
    }

    void write(String s)
    {
        for(int i=0; i < s.length(); i++)
        {
            this->addToBuffer(s[i]);
        }
    }

    void write(long l)
    {
        char buffer[sizeof(long)*8+1];
        sprintf(buffer, "%i", l);
        this->write(buffer);
    }

    void flush()
    {
        ::write(this->fileDescriptor, writeBuffer, BufferWriter::BUFFER_SIZE);
        memset(this->writeBuffer, 0, BufferWriter::BUFFER_SIZE);
        this->bufferPosition = 0;
    }
};

#endif
