#include "ParseTree.hpp"

String Decl::typeCheck()
{
    if(this->array)
    {
        if(this->arraySize <= 0)
            return "Error: Arraysize is null or negative.\n"; 
    }
    return "";
}

String Decls::typeCheck()
{
    String str = "";
    for(int i=0; i<decls->getSize();i++)
    {
        Decl *decl = this->decls->getValue(i);
        str += decl->typeCheck();
    }
    return str;
}

String Op::typeCheck()
{
    return "";
}

String OpExp::typeCheck()
{
    String str = "";
    if(exp != NULL)
        str += exp->typeCheck();
    if(op != NULL)
        str += op->typeCheck();
    return str;
}

String Index::typeCheck()
{
    if(this->exp == NULL)
        return "";
    return exp->typeCheck();
}

String Exp2_1::typeCheck()
{
    return exp->typeCheck();
}

String Exp2_2::typeCheck()
{
    return index->typeCheck();
}

String Exp2_3::typeCheck()
{
    return "";
}

String Exp2_4::typeCheck()
{
    return exp2->typeCheck();
}

String Exp2_5::typeCheck()
{
    return exp2->typeCheck();
}

String Exp::typeCheck()
{
    String str = "";
    Op *op = opexp->op;
    if(op == NULL)
    {
        str += opexp->typeCheck();
        str += exp2->typeCheck();
    }
    return str;
}

String Statement_1::typeCheck()
{
    String str = exp->typeCheck();
    str += index->typeCheck();
    return str;
}

String Statement_2::typeCheck()
{
    return exp->typeCheck();
}

String Statement_3::typeCheck()
{
    return "";
}

String Statement_4::typeCheck()
{
    return statements->typeCheck();
}

String Statement_5::typeCheck()
{
    String str = exp->typeCheck();
    str += statement1->typeCheck();

    if(statement2 != NULL)
    {
        str += statement2->typeCheck();    
    }

    return str;
}

String Statement_6::typeCheck()
{
    String str = "";

    str += exp->typeCheck();
    str += statement->typeCheck();

    return str;
}

String Statements::typeCheck()
{
    String str = "";
    for(int i=0; i<statements->getSize();i++)
    {
        Statement *statement = this->statements->getValue(i);
        str += statement->typeCheck();
    }
    return str;
}

String Prog::typeCheck()
{
    String str = this->decls->typeCheck();
    str += this->statements->typeCheck();
    return str;
}

