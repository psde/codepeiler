// Debug stuff...
#define NO_DIRECT_IO // Use this if developing on crypto fs

#ifndef __GNUC__  
    #error "You need GCC to compile this." 
#endif 

#include <iostream>
#include <iomanip>

// TODO: Beautfiy this
#include "String.hpp"
#include "BufferReader.hpp"
#include "BufferWriter.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "Symtable.hpp"
#include "Parser.hpp"

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
    std::ostream* out = &std::cout;
    
    Symtable *symtable = new Symtable(1024);
    
    Lexer *lex = new Lexer(buf, symtable);
    
    Parser *parser = new Parser(lex);

    ParseTree *foo = parser->parse();
    //std::cout << foo->dump() << std::endl;
    //std::cout << "Making code:" << std::endl << foo->makeCode() << std::endl;

    writer = new BufferWriter("codeout");
    out = &writer->stream();
    *out << foo->makeCode();
    delete writer;
    return 0;

    //TODO: Meh.

    if(output)
    {
        writer = new BufferWriter(outputFile);
        out = &writer->stream();
    }
    *out << std::setiosflags(std::ios::left);

    Token token;
    while(true)
    {
        token = lex->nextToken();

        if(token.getType() == Token::TOKEN_EOF)
            break;

        unsigned long tokenInteger;
        try
        {
            if(token.getType() == Token::TOKEN_INTEGER)
                tokenInteger = token.getLexem().toULong();

              *out << std::setw(20) 
                   << token.getTokenDescription() 
                   <<  " Line: " << std::setw(10) 
                   << token.getLine() << "Column: " 
                   << std::setw(10) << token.getColumn();

              if(token.getType() == Token::TOKEN_IDENTIFIER)
                  *out << " Lexem: " << token.getLexem();

              if(token.getType() == Token::TOKEN_INTEGER)
                  *out << " Value: " << tokenInteger;

              *out << std::endl;
        }
        catch(std::range_error e)
        {
            std::cout << "Line: " << token.getLine() 
                      << " Column: " << token.getColumn() 
                      << ": Error while trying to parse '" << token.getLexem() 
                      << "': Out of range." << std::endl;
        }
    }

    if(output)
    {
        delete writer;
    }

    delete buf;
    delete lex;
    delete symtable;

    return 0;
}
