#include "ParseTree.hpp"

static long& uniqueId()
{
    static long id = 1;
    return id;
}

static long getUniqueId()
{
    static long id = 1;
    id++;
    return id;
}

String Decl::makeCode()
{
    String str = "DS $";
    str += identifier;
    str += " ";
    if(this->array)
        str += (long)this->arraySize; 
    else
        str += "1";
    str += "\n";
    return str;
}

String Decls::makeCode()
{
    String str = "";
    for(int i=0; i<decls->getSize();i++)
    {
        Decl *decl = this->decls->getValue(i);
        str += decl->makeCode();
    }
    return str;
}

String Op::makeCode()
{
    //                  ADD    SUB    MUL    DUV    LES    EQU   >  <!>   AND   !
    String items[] = { "ADD", "SUB", "MUL", "DIV", "LES", "EQU", "", "", "AND", "" };

    String op = items[this->type];
    if(op != "")
    {
        String str = op;
        str += "\n";
        return str;
    }
    else
    {
        return "";
    }
}

String OpExp::makeCode()
{
    String str = exp->makeCode();
    str += op->makeCode();
    return str;
}

String Index::makeCode()
{
    if(this->exp == NULL)
        return "";
    String str = exp->makeCode();
    str += "ADD\n";
    return str;
}

String Exp2_1::makeCode()
{
    return exp->makeCode();
}

String Exp2_2::makeCode()
{
    String str = "LA $";
    str += identifier;
    str += "\n";

    str += index->makeCode();
    str += "LV\n";
    return str;
}

String Exp2_3::makeCode()
{
    String str = "LC ";
    str += integer;
    str += "\n";
    return str;
}

String Exp2_4::makeCode()
{
    String str = "LC 0\n";
    str += exp2->makeCode();
    str += "SUB\n";
    return str;
}

String Exp2_5::makeCode()
{
    String str = exp2->makeCode();
    str += "NOT\n";
    return str;
}

String Exp::makeCode()
{
    String str = "";
    Op *op = opexp->op;
    if(op == NULL)
    {
        str += exp2->makeCode();
    }
    else
    {
        switch(op->type)
        {
            case Op::OP_GREATER:
                str += opexp->makeCode();
                str += exp2->makeCode();
                str += "LES\n";
                break;
            case Op::OP_LER:
                str += opexp->makeCode();
                str += exp2->makeCode();
                str += "NOT\n";
                break;
            default:
                str += exp2->makeCode();
                str += opexp->makeCode();
                break;
        }
    }
    return str;
}

String Statement_1::makeCode()
{
    String str = exp->makeCode();
    str += "LA $";
    str += identifier;
    str += "\n";
    str += index->makeCode();
    str += "STR\n";
    return str;
}

String Statement_2::makeCode()
{
    String str = exp->makeCode();
    str += "PRI\n";
    return str;
}

String Statement_3::makeCode()
{
    String str = "REA\n";
    str += "LA $";
    str += identifier;
    str += "\n";
    str += "STR\n";
    return str;
}

String Statement_4::makeCode()
{
    return statements->makeCode();
}

String Statement_5::makeCode()
{
    String str = exp->makeCode();

    int jmp1 = getUniqueId();
    int jmp2 = getUniqueId();

    str += "JIN #jmp";
    str += jmp1;
    str += "\n";

    str += statement1->makeCode();
    
    // else
    if(statement2 != NULL)
    {
        str += "JMP #jmp";
        str += jmp2;
        str += "\n";
    }

    str += "#jmp";
    str += jmp1;
    str += " NOP\n";

    // else
    if(statement2 != NULL)
    {
        str += statement2->makeCode();    

        str += "#jmp";
        str += jmp2;
        str += " NOP\n";
    }

    return str;
}

String Statement_6::makeCode()
{
    String str = "";

    int jmp1 = getUniqueId();
    int jmp2 = getUniqueId();

    str += "#jmp";
    str += jmp1;
    str += " NOP\n";
    
    str += exp->makeCode();

    str += "JIN #jmp";
    str += jmp2;
    str += "\n";

    str += statement->makeCode();

    str += "JMP #jmp";
    str += jmp1;
    str += "\n";

    str += "#jmp";
    str += jmp2;
    str += " NOP\n";

    return str;
}

String Statements::makeCode()
{
    String str = "";
    for(int i=0; i<statements->getSize();i++)
    {
        Statement *statement = this->statements->getValue(i);
        str += statement->makeCode();
    }
    return str;
}

String Prog::makeCode()
{
    String str = this->decls->makeCode();
    str += this->statements->makeCode();
    str += "STP\n";
    return str;
}

