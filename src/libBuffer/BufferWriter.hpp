#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include <libStd/String.hpp>

class BufferWriter
{
private:
    static const int BUFFER_SIZE = 1024 * 4;
    
    int fileDescriptor;
    char* writeBuffer;
    int bufferPosition;

    void addToBuffer(char c);

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

    std::ostream& stream();

    BufferWriter(const char* file);

    ~BufferWriter();

    void write(const char* s, unsigned int length);

    void flush();
};
