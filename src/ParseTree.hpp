#pragma once

#include "ParserRule.hpp"
#include "Token.hpp"
#include "String.hpp"
#include "Vector.hpp"

class ParseTree
{
protected:

public:
    virtual String makeCode() = 0;
    virtual String dump() = 0;
    virtual String typeCheck() = 0;
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

    String dump() { return "!!THIS SHOULD NOT HAPPEN!!"; }
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

    String dump();   
    String typeCheck();
    String makeCode();
};

class Decls : public ParseTree
{
protected:
    Vector<Decl*> *decls;

public:
    Decls() { this->decls = new Vector<Decl*>(); }

    ~Decls() { delete this->decls; }
  
    void addDecl(Decl *decl) { this->decls->append(decl); }
    Vector<Decl*>* getDecls() { return this->decls; }

    String dump();    
    String typeCheck(); 
    String makeCode();
};

class Op : public ParseTree
{
public:
    enum OpType
    {
        OP_PLUS = 0,
        OP_MINUS,
        OP_MULT,
        OP_DIV,
        OP_LESSER,
        OP_EQUAL,
        OP_GREATER,
        OP_LER,
        OP_AND
    };

    OpType type;

    Op(OpType type) { this->type = type; }

    OpType getType() { return this->type; }

    String dump();   
    String typeCheck();
    String makeCode();
};

class Exp;
class OpExp : public ParseTree
{
public:
    Op *op;
    Exp *exp;
    
    OpExp() : op(NULL), exp(NULL) {}
    ~OpExp();

    void setOp(Op *op) { this->op = op; }
    Op* getOp() { return this->op; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump();   
    String typeCheck();
    String makeCode();
};

class Index : public ParseTree
{
protected:
    Exp *exp;

public:
    Index() : exp(NULL) {}
    ~Index();

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump();    
    String typeCheck();
    String makeCode();
};

class Exp2 : public ParseTree
{};

/* ( EXP ) */
class Exp2_1 : public Exp2
{
protected:
    Exp *exp;
public:
    ~Exp2_1();

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump();    
    String typeCheck();
    String makeCode();
};

/* identifier INDEX */
class Exp2_2 : public Exp2, public IdentifierParseTree
{
protected:
    Index *index;

public:
    ~Exp2_2();

    void setIndex(Index *index) { this->index = index; }
    Index* getIndex() { return this->index; }

    String dump();    
    String typeCheck();
    String makeCode();
};

/* integer */
class Exp2_3 : public Exp2
{
protected:
    long integer;
public:
    void setInteger(long integer) { this->integer = integer; }
    long getInteger() { return this->integer; }

    String dump();    
    String typeCheck();
    String makeCode();
};

/* - EXP2 */
class Exp2_4 : public Exp2
{
protected:
    Exp2 *exp2;
public:
    ~Exp2_4() { delete this->exp2; }

    void setExp2(Exp2 *exp2) { this->exp2 = exp2; }
    Exp2* getExp2() { return this->exp2; }

    String dump();   
    String typeCheck();
    String makeCode();
};

/* ! EXP2 */
class Exp2_5 : public Exp2
{
protected:
    Exp2 *exp2;
public:
    ~Exp2_5() { delete this->exp2; }

    void setExp2(Exp2 *exp2) { this->exp2 = exp2; }
    Exp2* getExp2() { return this->exp2; }

    String dump();   
    String typeCheck();
    String makeCode();
};

class Exp : public ParseTree
{
protected:
    Exp2* exp2;
    OpExp* opexp;

public:
    Exp() {}
    ~Exp() { delete this->exp2; delete this->opexp; }

    void addExp2(Exp2 *exp2) { this->exp2 = exp2; }
    Exp2* getExp2() { return this->exp2; }

    void addOpExp(OpExp *opexp) { this->opexp = opexp; }
    OpExp* getOpExp() { return this->opexp; }

    String dump();    
    String typeCheck();
    String makeCode();
};

class Statement : public ParseTree
{
public:
    String dump() { return ""; }
};

/* identifier INDEX = EXP */
class Statement_1 : public Statement, public IdentifierParseTree
{
protected:
    Index *index;
    Exp *exp;
public:
    Statement_1() : index(NULL), exp(NULL) {}
    ~Statement_1() { if(this->index != NULL) delete this->index; delete this->exp; }

    void setIndex(Index* index) { this->index = index; }
    Index* getIndex() { return this->index; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump();    
    String typeCheck();
    String makeCode();
};

/* print ( EXP ) */
class Statement_2 : public Statement
{
protected:
    Exp *exp;
public:
    ~Statement_2() { delete this->exp; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump();  
    String typeCheck();
    String makeCode();
};

/* read ( EXP )*/
class Statement_3 : public Statement
{
protected:
    Exp *exp;
public:
    ~Statement_3() { delete this->exp; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    String dump();    
    String typeCheck();
    String makeCode();
};

class Statements;
/* { STATEMENTS } */
class Statement_4 : public Statement
{
protected:
    Statements *statements;
public:
    ~Statement_4(); 

    void setStatements(Statements* statements) { this->statements = statements; }
    Statements* getStatements() { return this->statements; }

    String dump();    
    String typeCheck();
    String makeCode();
};

/* if ( EXP ) STATEMENT else STATEMENT */
class Statement_5 : public Statement
{
protected:
    Statement *statement1;
    Statement *statement2;
    Exp *exp;
public:
    Statement_5() : statement1(NULL), statement2(NULL) {}
    ~Statement_5() { delete this->exp; delete this->statement1; if(this->statement2 != NULL) delete this->statement2; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }
    
    void setStatement1(Statement* statement) { this->statement1 = statement; }
    Statement* getStatement1() { return this->statement1; }

    void setStatement2(Statement* statement) { this->statement2 = statement; }
    Statement* getStatement2() { return this->statement2; }

    String dump();    
    String typeCheck();
    String makeCode();
};

/* while ( EXP ) statement */
class Statement_6 : public Statement
{
protected:
    Exp *exp;
    Statement *statement;
public:
    ~Statement_6() { delete this->statement; delete this->exp; }

    void setExp(Exp *exp) { this->exp = exp; }
    Exp* getExp() { return this->exp; }

    void setStatement(Statement* statement) { this->statement = statement; }
    Statement* getStatement() { return this->statement; }

    String dump();   
    String typeCheck();
    String makeCode();
};

class Statements : public ParseTree
{
protected:
    Vector<Statement*> *statements;
public:
    Statements() { this->statements = new Vector<Statement*>(); }

    ~Statements() { delete this->statements;  }

    void addStatement(Statement *statement) { this->statements->append(statement); }
    Vector<Statement*>* getStatements() { return this->statements; }

    String dump();  
    String typeCheck();
    String makeCode();
};

class Prog : public ParseTree 
{
protected:
    Decls *decls;
    Statements *statements;

public:
    Prog() {}
    ~Prog() { delete this->decls; delete this->statements; }

    void addDecls(Decls *decls) { this->decls = decls; }
    Decls* getDecls() { return this->decls; }

    void addStatements(Statements *statements) { this->statements = statements; }
    Statements* getStatements() { return this->statements; }

    String dump();  
    String typeCheck();
    String makeCode();
};
