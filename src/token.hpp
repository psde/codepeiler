#ifndef TOKEN_HPP
#define TOKEN_HPP


typedef int TType;

class Token
{
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
};

#endif
