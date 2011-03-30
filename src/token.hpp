#ifndef TOKEN_HPP
#define TOKEN_HPP


//typedef int TType;

class Token
{
public:
    enum TType
    {
        TOKEN_INVALID = 0,
        TOKEN_IDENTIFIER,
        TOKEN_INTEGER,
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_DIV,
        TOKEN_MULT,
        TOKEN_EQUAL,
        TOKEN_EOF
    };

private:

	TType tokenType;
	int lineNumber;
	int columnNumber;

public:

	Token(TType type, int line, int column)
	{
		this->tokenType = type;
		this->lineNumber = line;
		this->columnNumber = column;
	}

    Token()
    {
        this->tokenType = Token::TOKEN_INVALID;
        this->lineNumber = -1;
        this->columnNumber = -1;
    }

    void setPosition(int line, int column)
    {
        this->lineNumber = line;
        this->columnNumber = column;
    }

	int line()
	{	
		return this->lineNumber;
	}

	int column()
	{
		return this->columnNumber;
	}

	TType type()
	{
		return this->tokenType;
	}

    void type(TType token)
    {
        this->tokenType = token;
    }
};

#endif
