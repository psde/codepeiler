#ifndef BUFFERWRITER_HPP
#define BUFFERWRITER_HPP

#include <errno.h>
#include <iostream>
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

    class StreamBuf : public std::streambuf
    {
    public:
        StreamBuf(BufferWriter& writer) : writer(writer) {}


        std::streamsize xsputn(const char* s, std::streamsize n)
        {
            writer.write(s, n);
            return n;
        }

        int sync()
        {
            //writer.flush();
            return 0;
        }

        int overflow(int c = -1) {
            if (c != -1)
            {
                char ch = c;
                writer.write(&ch, 1);
            }
            //writer.flush();
            return 0;
        }

    private:
        BufferWriter& writer;

        StreamBuf(const StreamBuf&);
        StreamBuf& operator=(const StreamBuf&);
    };

    StreamBuf streambuf;

    std::ostream ostream;

public:

    std::ostream& stream()
    {
        return ostream;
    }

    BufferWriter(const char* file)
      : streambuf(*this), ostream(&streambuf)
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

    void write(const char* s, unsigned int length)
    {
        for(unsigned int i=0; i < length; i++)
        {
            this->addToBuffer(s[i]);
        }
    }

    void flush()
    {
        ::write(this->fileDescriptor, writeBuffer, BufferWriter::BUFFER_SIZE);
        memset(this->writeBuffer, 0, BufferWriter::BUFFER_SIZE);
        this->bufferPosition = 0;
    }
};

#endif
