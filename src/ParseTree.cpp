#include "ParseTree.hpp"

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

Statement_4::~Statement_4()
{
    delete this->statements;
}
