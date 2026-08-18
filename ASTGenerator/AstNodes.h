#pragma once
#include "Token.h"

struct Expression{};

struct Binary : public Expression
{
	Binary ( Expression left, Token* operator, Expression right){}
 Expression left;
Token* operator;
Expression right;
};struct Grouping : public Expression
{
	Grouping ( Expression expression){}
 Expression expression;
};struct Literal : public Expression
{
	Literal ( std::Any value){}
 std::Any value;
};struct Unary : public Expression
{
	Unary ( Token* operator, Expression right){}
 Token* operator;
Expression right;
};struct : public Expression
{
	(){}
};