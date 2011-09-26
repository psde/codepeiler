#ifndef PARSETREE_HPP
#define PARSETREE_HPP

#include "ParserRule.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "String.hpp"
#include "Vector.hpp"

class ParseTree
{
protected:

public:
    //virtual void makeCode() = 0;
    virtual String dump() = 0;
};

class IdentifierParseTree : public ParseTree
{
protected:
    String identifier;

public:
    IdentifierParseTree(String identifier = "")
     : identifier(identifier) {}

    String getIdentifier() { return this->identifier; }
    void setIdentifier(String identifier) { this->identifier = identifier; }

    String dump() { return ""; }
};

class Decl : public IdentifierParseTree
{
protected:
    bool array;
    int arraySize;

public:
    Decl(String identifier = "")
     : IdentifierParseTree(identifier) {}

    bool getArray() { return this->array; }
    int getArraySize() { return this->arraySize; }
    void setArray(int size) { this->array = true; this->arraySize = size; }

    String dump() 
    { 
        String str = "int ";
        str += this->identifier;
        if(this->array)
        {
            str += "[";
            str += (long)this->arraySize;
            str += "]";
        }
        return str;
    }
};

class Decls : public ParseTree
{
protected:
    Vector<Decl*> *decls;

public:
    Decls() { this->decls = new Vector<Decl*>(); }

    //~Decls() { delete this->decls; }
  
    void addDecl(Decl *decl) { this->decls->append(decl); }
    Vector<Decl*>* getDecls() { return this->decls; }

    String dump() 
    {
        String str = "";
        for(int i=0; i<decls->getSize();i++)
        {
            Decl *decl = this->decls->getValue(i);
            str += decl->dump();
            
            str += "; ";
        }
        return str;
    } 
};

class Op : public ParseTree
{
public:
    enum OpType
    {
        OP_PLUS,
        OP_MINUS,
        OP_MULT,
        OP_DIV,
        OP_LESSER,
        OP_EQUAL,
        OP_GREATER,
        OP_LER,
        OP_AND
    };

protected:
    OpType type;

public:
    Op(OpType type) { this->type = type; }

    OpType getType() { return this->type; }

    String dump() { return ""; }
};

class Exp;
class OpExp : public ParseTree
{
protected:
    Op *op;
    Exp *exp;
public:
    OpExp() : op(NULL), exp(NULL) {}
    //~OpExp() { if(op != NULL) delete op; if(exp != NULL) delete exp; }

    void setOp(Op *op) { this->op = op; }
    Op* getOp() { return this->op; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump() { return ""; }
};

class Index : public ParseTree
{
protected:
    Exp *exp;

public:
    Index() : exp(NULL) {}
    //~Index() { if(exp != NULL) delete this->exp; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump() { return ""; }
};

class Exp2 : public ParseTree
{};

/* ( EXP ) */
class Exp2_1 : public Exp2
{
protected:
    Exp *exp;
public:
    //~Exp2_1() { delete exp; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump() { return ""; }
};

/* identifier INDEX */
class Exp2_2 : public Exp2, public IdentifierParseTree
{
protected:
//    String identifier;
    Index *index;

public:
    //~Exp2_2() { delete this->index; }

/*    void setIdentifier(String identifier) { this->identifier = identifier; }
    String getIdentifier() { return this->identifier; }*/

    void setIndex(Index *index) { this->index = index; }
    Index* getIndex() { return this->index; }

    String dump() { return ""; }
};

/* integer */
class Exp2_3 : public Exp2
{
protected:
    long integer;
public:
    void setInteger(long integer) { this->integer = integer; }
    long getInteger() { return this->integer; }

    String dump() { return ""; }
};

/* - EXP2 */
/* ! EXP2 */

class Exp : public ParseTree
{
protected:
    Exp2* exp2;
    OpExp* opexp;

public:
    Exp() {}
    //~Exp() { delete this->exp2; delete this->opexp; }

    void addExp2(Exp2 *exp2) { this->exp2 = exp2; }
    Exp2* getExp2() { return this->exp2; }

    void addOpExp(OpExp *opexp) { this->opexp = opexp; }
    OpExp* getOpExp() { return this->opexp; }

    String dump() { return ""; }
};

class Statement : public ParseTree
{
public:
    virtual String dump() { return ""; }
};

class Statements : public ParseTree
{
protected:
    Vector<Statement*> *statements;
public:
    Statements() { this->statements = new Vector<Statement*>(); }

    //~Statements() { delete this->statements;  }

    void addStatement(Statement *statement) { this->statements->append(statement); }
    Vector<Statement*>* getStatements() { return this->statements; }

    String dump() { return ""; }
};

class Prog : public ParseTree 
{
protected:
    Decls *decls;
    Statements *statements;

public:
    Prog() {}
    //~Prog() { delete this->decls; delete this->statements; }

    void addDecls(Decls *decls) { this->decls = decls; }
    Decls* getDecls() { return this->decls; }

    void addStatements(Statements *statements) { this->statements = statements; }
    Statements* getStatements() { return this->statements; }

    String dump() 
    {
        String str = "Dumping decls:\n";
        str += this->decls->dump();
        str += "\n";
        return str;
    }
};

#endif
