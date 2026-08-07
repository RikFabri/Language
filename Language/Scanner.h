#pragma once
#include "Token.h"

#include <vector>

class Scanner
{
public:
	Scanner(std::string_view source);

	void ScanTokens();

	bool IsAtEnd() const;
	void PrintTokens() const;

private:
	void ScanToken();
	char Advance();
	bool Match(char expected);
	
	void AddToken(TokenType type);

	std::vector<Token> m_Tokens;
	std::string_view m_Source;

	int m_Line = 1;
	int m_Current = 0;
	int m_Start = 0;
};

