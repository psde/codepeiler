#include <iostream>
#include <iomanip>

#include "string.hpp"
#include "buffer.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "hashtable.hpp"
#include "symtable.hpp"

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

    Buffer *buf = new Buffer(argv[1]);
    Lexer *lex = new Lexer(buf);
    Symtable symtable(100);

    std::cout << std::setiosflags(std::ios::left) << std::endl;

    if(!output)
    {
        std::cout << "  " << std::setw(6) << "line" << std::setw(8) << "column" << std::setw(20) << "token" << std::setw(16) << "lexem" << std::endl;
        std::cout << "  --------------------------------------------------------" << std::endl;
    }
    else
    {
        freopen(outputFile, "w+", stdout);
    }

    Token token;
    while(true)
    {
        token = lex->nextToken();

        // Add IDENTIFIER to symtable
        if(token.getType() == Token::TOKEN_IDENTIFIER)
        {
            Entry* e;

            if(symtable.contains(token.getLexem()))
            {
                // Identifier already in symtable, this could mean this is a keyword (print, read, ...)
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
        
        if(!output)
        {
            std::cout << "  " << std::setw(6) << token.getLine() << std::setw(8) << token.getColumn() << std::setw(20) << token.echo() << std::setw(16) << token.getLexem();
            if(token.getType() == Token::TOKEN_INTEGER)
                std::cout << " Value: " << token.getLexem().toULong();
            std::cout << std::endl;
        }
        else
        {
            // TODO: File output
            std::cout << std::setw(20) << token.echo() <<  " Line: " << std::setw(5) << token.getLine() << "Column: " << std::setw(5) << token.getColumn();
            if(token.getType() == Token::TOKEN_IDENTIFIER)
                std::cout << " Lexem: " << token.getLexem();

            if(token.getType() == Token::TOKEN_INTEGER)
                std::cout << " Value: " << token.getLexem().toULong();
    
            std::cout << std::endl;
        }
         
        if(token.getType() == Token::TOKEN_EOF)
            break;
    }

    if(output)
    {
        fclose(stdout);
    }

    return 0;
}
