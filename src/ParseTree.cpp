#include "ParseTree.hpp"

// This is kinda weird, but we need this for a few classes to be outside the header

OpExp::~OpExp() 
{ 
    if(op != NULL) delete op; 
    if(exp != NULL) delete exp; 
}

Index::~Index() 
{ 
    if(exp != NULL) delete this->exp; 
}

String Index::dump()
{ 
    if(exp != NULL)
    {
        String str = "[";
        str += exp->dump();
        str += "]";
        return str; 
    }
    return "";
}

Exp2_1::~Exp2_1() 
{ 
    delete exp; 
}

String Exp2_1::dump() 
{
    String str = "(";
    str += exp->dump();
    str += ")";
    return str; 
}

Exp2_2::~Exp2_2() 
{ 
    delete this->index; 
}

Statement_4::~Statement_4()
{
    delete this->statements;
}

String Statement_4::dump() 
{ 
    String str = "{\n";
    str += statements->dump();
    str += "}";
    return str; 
}

String OpExp::dump()
{
    String str = "";
    if(this->op != NULL && this->exp != NULL)
    {
        str += op->dump();
        str += exp->dump();
    }
    return str; 
}

String Op::dump()
{
    String items[] = { "+", "-", "*", "/", "<", "=", ">", "<=>", "&", "!" };

    String str = " ";
    str += items[this->type];
    str += " ";
    return str;
}

String Exp2_4::dump()
{
    String str = "-";
    str += exp2->dump();
    return str;
}

String Exp2_5::dump()
{
    String str = "!";
    str += exp2->dump();
    return str;
}
