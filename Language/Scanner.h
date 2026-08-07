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
	char Peek() const;
	char PeekNext(unsigned offset = 1) const;
	bool Match(char expected);
	std::string_view GetCurrentLexeme() const;
	
	void AddToken(TokenType type, std::string_view value = "");
	void Error(std::string_view error);

	void HandleComment();
	void HandleString();
	void HandleNumber();
	void HandleIdentifier();

	static TokenType GetReservedKeywordOrIdentifier(std::string_view lexeme);
	static bool IsAlphaNumeric(char c);

	std::vector<Token> m_Tokens;
	std::string_view m_Source;

	int m_Line = 1;
	int m_Current = 0;
	int m_Start = 0;
};

