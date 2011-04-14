#include <iostream>
#include <iomanip>

#include "string.hpp"
#include "buffer.hpp"
#include "token.hpp"
#include "lexer.hpp"
#include "hashtable.hpp"

// TODO: This needs to go somewhere else
class Entry
{

public:
    Token::TType type;
    String lexem;

    Entry(Token::TType t, String l)
    {
        this->type = t;
        this->lexem = l;
    }
};


int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << "usage: \tcodepeiler input [output]" << std::endl;
        std::cout << "\t\tinput: source code file to be analysed." << std::endl;
        std::cout << "\t\toutput: optional, will write output to. stdout is used by default." << std::endl;
        return 0;
    }

    String output = "";

    if(argc == 3)
    {
        output = argv[2];
    }

    Buffer *buf = new Buffer(argv[1]);
    Lexer *lex = new Lexer(buf);
    Hashtable<Entry*> symtable(100);

    symtable.put("print", new Entry(Token::TOKEN_PRINT, "print"));
    symtable.put("read", new Entry(Token::TOKEN_READ, "read"));

    if(output == "")
    {
        std::cout << std::setiosflags(std::ios::left) << std::endl;
        std::cout << "  " << std::setw(6) << "line" << std::setw(8) << "column" << std::setw(20) << "token" << std::setw(16) << "lexem" << std::endl;
        std::cout << "  --------------------------------------------------------" << std::endl;
    }

    Token token;
    while(true)
    {
        token = lex->nextToken();

        // Add IDENTIFIER to symtable
        if(token.type() == Token::TOKEN_IDENTIFIER)
        {
            if(symtable.contains(token.lexem()))
            {
                // Identifier already in symtable, this could mean this is a keyword (print, read, ...)
                token.type(symtable.get(token.lexem())->type);
            }
            else
            {
                symtable.put(token.lexem(), new Entry(token.type(), token.lexem()));
            }
        }
        
        if(output == "")
        {
            std::cout << "  " << std::setw(6) << token.line() << std::setw(8) << token.column() << std::setw(20) << token.echo() << std::setw(16) << token.lexem();
            if(token.type() == Token::TOKEN_INTEGER)
                std::cout << " Value: " << token.lexem().toULong();
            std::cout << std::endl;
        }
        else
        {
            // TODO: File output
        }
         
        if(token.type() == Token::TOKEN_EOF)
            break;
    }

    return 0;
}
