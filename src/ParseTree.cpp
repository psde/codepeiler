#include "ParseTree.hpp"

// This is kinda weird, but we need this for a few classes to be outside the heaer

OpExp::~OpExp() 
{ 
    if(op != NULL) delete op; 
    if(exp != NULL) delete exp; 
}

Index::~Index() 
{ 
    if(exp != NULL) delete this->exp; 
}

Exp2_1::~Exp2_1() 
{ 
    delete exp; 
}

Exp2_2::~Exp2_2() 
{ 
    delete this->index; 
}
