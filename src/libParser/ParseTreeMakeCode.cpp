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

void Decl::makeCode(std::ostream *out)
{
    *out << "DS $";
    *out << identifier;
    *out << " ";
    if(this->array)
        *out << (long)this->arraySize; 
    else
        *out << "1";
    *out << "\n";
}

void Decls::makeCode(std::ostream *out)
{
    *out << "";
    for(int i=0; i<decls->getSize();i++)
    {
        Decl *decl = this->decls->getValue(i);
        decl->makeCode(out);
    }
}

void Op::makeCode(std::ostream *out)
{
    //                  ADD    SUB    MUL    DUV    LES    EQU   >  <!>   AND   !
    static String items[] = { "ADD", "SUB", "MUL", "DIV", "LES", "EQU", "", "EQU", "AND", "" };

    String op = items[this->type];
    if(op != "")
    {
        *out << op;
        *out << "\n";
    }
    else
    {
        return; //return "";
    }
}

void OpExp::makeCode(std::ostream *out)
{
    exp->makeCode(out);
    op->makeCode(out);
}

void Index::makeCode(std::ostream *out)
{
    if(this->exp == NULL)
        return; //return "";
    exp->makeCode(out);
    *out << "ADD\n";
}

void Exp2_1::makeCode(std::ostream *out)
{
    return exp->makeCode(out);
}

void Exp2_2::makeCode(std::ostream *out)
{
    *out << "LA $";
    *out << identifier;
    *out << "\n";

    index->makeCode(out);
    *out << "LV\n";
}

void Exp2_3::makeCode(std::ostream *out)
{
    *out << "LC ";
    *out << integer;
    *out << "\n";
}

void Exp2_4::makeCode(std::ostream *out)
{
    *out << "LC 0\n";
    exp2->makeCode(out);
    *out << "SUB\n";
}

void Exp2_5::makeCode(std::ostream *out)
{
    exp2->makeCode(out);
    *out << "NOT\n";
}

void Exp::makeCode(std::ostream *out)
{
    *out << "";
    Op *op = opexp->op;
    if(op == NULL)
    {
        exp2->makeCode(out);
    }
    else
    {
        switch(op->type)
        {
            case Op::OP_GREATER:
                opexp->makeCode(out);
                exp2->makeCode(out);
                *out << "LES\n";
                break;
            case Op::OP_LER:
                exp2->makeCode(out);
                opexp->makeCode(out);
                *out << "NOT\n";
                break;
            default:
                exp2->makeCode(out);
                opexp->makeCode(out);
                break;
        }
    }
}

void Statement_1::makeCode(std::ostream *out)
{
    exp->makeCode(out);
    *out << "LA $";
    *out << identifier;
    *out << "\n";
    index->makeCode(out);
    *out << "STR\n";
}

void Statement_2::makeCode(std::ostream *out)
{
    exp->makeCode(out);
    *out << "PRI\n";
}

void Statement_3::makeCode(std::ostream *out)
{
    *out << "REA\n";
    *out << "LA $";
    *out << identifier;
    *out << "\n";
    *out << "STR\n";
}

void Statement_4::makeCode(std::ostream *out)
{
    return statements->makeCode(out);
}

void Statement_5::makeCode(std::ostream *out)
{
    exp->makeCode(out);

    int jmp1 = getUniqueId();
    int jmp2 = getUniqueId();

    *out << "JIN #jmp";
    *out << jmp1;
    *out << "\n";

    statement1->makeCode(out);
    
    // else
    if(statement2 != NULL)
    {
        *out << "JMP #jmp";
        *out << jmp2;
        *out << "\n";
    }

    *out << "#jmp";
    *out << jmp1;
    *out << " NOP\n";

    // else
    if(statement2 != NULL)
    {
        statement2->makeCode(out);    

        *out << "#jmp";
        *out << jmp2;
        *out << " NOP\n";
    }

}

void Statement_6::makeCode(std::ostream *out)
{
    *out << "";

    int jmp1 = getUniqueId();
    int jmp2 = getUniqueId();

    *out << "#jmp";
    *out << jmp1;
    *out << " NOP\n";
    
    exp->makeCode(out);

    *out << "JIN #jmp";
    *out << jmp2;
    *out << "\n";

    statement->makeCode(out);

    *out << "JMP #jmp";
    *out << jmp1;
    *out << "\n";

    *out << "#jmp";
    *out << jmp2;
    *out << " NOP\n";

}

void Statements::makeCode(std::ostream *out)
{
    *out << "";
    for(int i=0; i<statements->getSize();i++)
    {
        Statement *statement = this->statements->getValue(i);
        statement->makeCode(out);
    }
}

void Prog::makeCode(std::ostream *out)
{
    this->decls->makeCode(out);
    this->statements->makeCode(out);
    *out << "STP\n";
}

