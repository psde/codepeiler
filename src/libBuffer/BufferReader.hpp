#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

class BufferReader
{
private:
    static const int BUFFER_SIZE = 1024 * 8;
    int fileDescriptor;
    ssize_t fileLength;
    ssize_t filePosition;
    char* fileBuffer;

    ssize_t bufferPosition;

public:
    BufferReader(const char* file);

    ~BufferReader();

    // Peeks the next char in buffer
    unsigned char peekChar();

    // Gets next char in buffer
    unsigned char getChar();

    // Set the buffer position back
    void ungetChar(int count);
};
