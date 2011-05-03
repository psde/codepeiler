#include <iostream>
#include <iomanip>

#include "string.hpp"
#include "buffer.hpp"
#include "token.hpp"
#include "lexer.hpp"
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

    // Redirect stdout to file if needed
    if(output)
    {
        freopen(outputFile, "w+", stdout);
    }

    std::cout << std::setiosflags(std::ios::left);

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
        
        std::cout << std::setw(20) << token.getTokenDescription() <<  " Line: " << std::setw(5) << token.getLine() << "Column: " << std::setw(5) << token.getColumn();
        
        if(token.getType() == Token::TOKEN_IDENTIFIER)
            std::cout << " Lexem: " << token.getLexem();

        if(token.getType() == Token::TOKEN_INTEGER)
            std::cout << " Value: " << token.getLexem().toULong();

        std::cout << std::endl;
    }

    if(output)
    {
        fclose(stdout);
    }

    return 0;
}
