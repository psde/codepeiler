// Debug stuff...
#define NO_DIRECT_IO // Use this if developing on crypto fs

#define VERSION "0.1"

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

    std::cout << std::endl << "Codepeiler v" << VERSION << " started." << std::endl;

    char* outputFile;
    bool output = false;
    //bool lexerOut = false;
    if(argc == 3)
    {
        outputFile = argv[2];
        output = true;
    }

    BufferReader *buf = new BufferReader(argv[1]);
    BufferWriter *writer;
    std::ostream* out = &std::cout;
 
    if(output)
    {
        std::cout << "Using file '" << outputFile << "' for code output." << std::endl;
        writer = new BufferWriter(outputFile);
        out = &writer->stream();
    }
    else
    {
        std::cout << "Using stdout for code output." << std::endl;
    }

    Symtable *symtable = new Symtable(1024);
    
    Lexer *lex = new Lexer(buf, symtable);
    
    Parser *parser = new Parser(lex);
   
    ParseTree *tree;
    std::cout << "Parsing... "; // << std::endl;
    try
    {
        tree = parser->parse();
    } 
    catch (ParserError err)
    {
        std::cout << "failed." << std::endl;
        std::cout << err.what() << std::endl;
        std::cout << "Exiting." << std::endl;
        return 1;
    }
    std::cout << "done." << std::endl;

    if(output)
    {
        writer = new BufferWriter(outputFile);
        out = &writer->stream();
    }
    //*out << std::setiosflags(std::ios::left);

    std::cout << "Type checking... ";
    String typecheck = tree->typeCheck();
    if(typecheck != "")
    {
        std::cout << "failed." << std::endl;
        std::cout << typecheck << std::endl;
        return 1;
    }

    std::cout << "done." << std::endl;

    std::cout << "Generating code... ";
    *out << tree->makeCode() << std::endl;
    std::cout << "done." << std::endl;

    /*Token token;
    while(lexerOut && true)
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
    }*/

    if(output)
    {
        delete writer;
    }

    delete buf;
    delete lex;
    delete symtable;

    std::cout << "Finished." << std::endl;
    return 0;
}
