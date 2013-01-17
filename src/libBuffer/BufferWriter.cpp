#include "BufferWriter.hpp"

BufferWriter::BufferWriter(const char* file)
  : streambuf(*this), ostream(&streambuf)
{
#ifdef NO_DIRECT_IO
    this->fileDescriptor = open(file, O_DIRECT | O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
#else
    this->fileDescriptor = open(file, O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU);
#endif
    this->writeBuffer = (char*)valloc(BufferWriter::BUFFER_SIZE);
    memset(this->writeBuffer, 0x20, BufferWriter::BUFFER_SIZE);

    this->bufferPosition = 0;
}

BufferWriter::~BufferWriter()
{
    this->flush();
    free(this->writeBuffer);
}

void BufferWriter::addToBuffer(char c)
{
    this->writeBuffer[bufferPosition++] = c;

    if(this->bufferPosition >= BufferWriter::BUFFER_SIZE)
        this->flush();
}

std::ostream& BufferWriter::stream()
{
    return ostream;
}

void BufferWriter::write(const char* s, unsigned int length)
{
    for(unsigned int i=0; i < length; i++)
    {
        this->addToBuffer(s[i]);
    }
}

void BufferWriter::flush()
{
    ssize_t writtenSize = ::write(this->fileDescriptor, writeBuffer, BufferWriter::BUFFER_SIZE);
    memset(this->writeBuffer, 0, writtenSize);
    this->bufferPosition = 0;
}
