#ifndef SYMTABLE_HPP
#define SYMTABLE_HPP

#include "hashtable.hpp"
#include "entry.hpp"

class Symtable : public Hashtable<Entry*>
{
public:
    Symtable(int i) : Hashtable<Entry*>(i) {};    

    void initSymbols()
    {

    }
};

#endif
