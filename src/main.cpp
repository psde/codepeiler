#include <iostream>
#include <iomanip>

#include "String.hpp"
#include "BufferReader.hpp"
#include "BufferWriter.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "Symtable.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << "usage: \tcodepeiler input [output]" << std::endl;
        std::cout << "\t\tinput: source code file to be analysed." << std::endl;
        std::cout << "\t\toutput: optional, will write output to. stdout is used by default." << std::endl;
        return 0;
    }

    char* outputFile;
    bool output = false;

    if(argc == 3)
    {
        outputFile = argv[2];
        output = true;
    }

    BufferReader *buf = new BufferReader(argv[1]);
    BufferWriter *writer;
    Lexer *lex = new Lexer(buf);
    Symtable symtable(100);

    if(output)
    {
        writer = new BufferWriter(outputFile);
    }
    else
    {
        std::cout << std::setiosflags(std::ios::left);
    }

    Token token;
    while(true)
    {
        token = lex->nextToken();

        if(token.getType() == Token::TOKEN_EOF)
            break;

        if(token.getType() == Token::TOKEN_IDENTIFIER)
        {
            Entry* e;

            if(symtable.contains(token.getLexem()))
            {
                e = symtable.get(token.getLexem());
                token.setType(e->type);
            }
            else
            {   
                e = new Entry(token.getType(), token.getLexem());
                symtable.put(token.getLexem(), e);
            }
            token.setEntry(e);
        }
        
        // 
        unsigned long tokenInteger;
        try
        {
            if(token.getType() == Token::TOKEN_INTEGER)
                tokenInteger = token.getLexem().toULong();

            if(output)
            {
                writer->write(token.getTokenDescription());
                writer->write(" Line: ");
                writer->write(token.getLine());
                writer->write(" Column: ");
                
                if(token.getType() == Token::TOKEN_IDENTIFIER)
                {
                    writer->write(" Lexem: ");
                    writer->write(token.getLexem());
                }

                if(token.getType() == Token::TOKEN_INTEGER)
                {
                    writer->write(" Value: ");
                    writer->write(tokenInteger);
                }

                writer->write("\n");
            }
            else
            {
                std::cout << std::setw(20) << token.getTokenDescription() <<  " Line: " << std::setw(10) << token.getLine() << "Column: " << std::setw(10) << token.getColumn();

                if(token.getType() == Token::TOKEN_IDENTIFIER)
                    std::cout << " Lexem: " << token.getLexem();
                
                if(token.getType() == Token::TOKEN_INTEGER)
                    std::cout << " Value: " << tokenInteger;

                std::cout << std::endl;
            }
        }
        catch(std::range_error e)
        {
            std::cout << "Line: " << token.getLine() << " Column: " << token.getColumn() << ": Error while trying to parse '" << token.getLexem() << "': Out of range." << std::endl;
        }
    }

    if(output)
    {
        delete writer;
    }

    delete buf;
    delete lex;

    return 0;
}
