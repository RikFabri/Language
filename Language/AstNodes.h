#pragma once
#include "Token.h"

struct Expression
{
};

struct Binary : public Expression
{
	Binary(Expression left, Token* pOperator, Expression right) : m_Left(left), m_pOperator(pOperator), m_Right(right) {}

	Expression m_Left;
	Token* m_pOperator;
	Expression m_Right;
};