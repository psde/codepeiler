#include "ParserRule.hpp"

Token::TType TOKENS_NONE[] =
{
    Token::TOKEN_INVALID
};
const ParserRule RULE_NONE = {
    "RULE_NONE",
    sizeof(TOKENS_NONE) / sizeof(TOKENS_NONE[0]),
    TOKENS_NONE
};

Token::TType TOKENS_PROG[] =
{
    Token::TOKEN_PRINT,
    Token::TOKEN_READ,
    Token::TOKEN_INT,
    Token::TOKEN_IDENTIFIER,
    Token::TOKEN_IF,
    Token::TOKEN_WHILE
};
const ParserRule RULE_PROG = {
    "RULE_PROG",
    sizeof(TOKENS_PROG) / sizeof(TOKENS_PROG[0]),
    TOKENS_PROG
};

Token::TType TOKENS_DECLS[] =
{
    Token::TOKEN_INT
};
const ParserRule RULE_DECLS = {
    "RULE_DECLS",
    sizeof(TOKENS_DECLS) / sizeof(TOKENS_DECLS[0]),
    TOKENS_DECLS
};

const ParserRule RULE_DECL = {
    "RULE_DECL",
    sizeof(TOKENS_DECLS) / sizeof(TOKENS_DECLS[0]),
    TOKENS_DECLS
};

const ParserRule RULE_TYPE_INT = {
    "RULE_TYPE_INT",
    sizeof(TOKENS_DECLS) / sizeof(TOKENS_DECLS[0]),
    TOKENS_DECLS
};

const ParserRule RULE_STATEMENT = {
    "RULE_STATEMENT",
    sizeof(TOKENS_NONE) / sizeof(TOKENS_NONE[0]),
    TOKENS_NONE
};

Token::TType TOKENS_STATEMENTS[] =
{
    Token::TOKEN_PRINT,
    Token::TOKEN_READ,
    Token::TOKEN_IDENTIFIER,
    Token::TOKEN_IF,
    Token::TOKEN_ELSE,
    Token::TOKEN_WHILE
};
const ParserRule RULE_STATEMENTS = {
    "RULE_STATEMENTS",
    sizeof(TOKENS_STATEMENTS) / sizeof(TOKENS_STATEMENTS[0]),
    TOKENS_STATEMENTS
};

Token::TType TOKENS_OP[] =
{
    Token::TOKEN_PLUS, Token::TOKEN_MINUS, Token::TOKEN_MULT, Token::TOKEN_DIV, Token::TOKEN_LESSER, Token::TOKEN_GREATER, Token::TOKEN_EQUAL, Token::TOKEN_AND, Token::TOKEN_LER
};
const ParserRule RULE_OP = {
    "RULE_OP",
    sizeof(TOKENS_OP) / sizeof(TOKENS_OP[0]),
    TOKENS_OP
};

Token::TType TOKENS_EXP2[] =
{
    Token::TOKEN_PAREN_L, Token::TOKEN_IDENTIFIER, Token::TOKEN_INTEGER, Token::TOKEN_MINUS, Token::TOKEN_NOT
};
const ParserRule RULE_EXP2 = {
    "RULE_EXP2",
    sizeof(TOKENS_EXP2) / sizeof(TOKENS_EXP2[0]),
    TOKENS_EXP2
};


