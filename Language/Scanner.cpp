#include "Scanner.h"
#include <iostream>
#include <cassert>
#include "ErrorReporting.h"


Scanner::Scanner(std::string_view source)
	: m_Source(source)
{
}

void Scanner::ScanTokens()
{
	while (!IsAtEnd())
	{
		m_Start = m_Current;

		ScanToken();
	}

	m_Tokens.emplace_back(TokenType::EOD, "", m_Line);
}

void Scanner::ScanToken()
{
	char c = Advance();
	switch (c)
	{
		case '(': AddToken(TokenType::LEFT_PAREN); break;
		case ')': AddToken(TokenType::RIGHT_PAREN); break;
		case '{': AddToken(TokenType::LEFT_BRACE); break;
		case '}': AddToken(TokenType::RIGHT_BRACE); break;
		case ',': AddToken(TokenType::COMMA); break;
		case '.': AddToken(TokenType::DOT); break;
		case '-': AddToken(TokenType::MINUS); break;
		case '+': AddToken(TokenType::PLUS); break;
		case ';': AddToken(TokenType::SEMICOLON); break;
		case '*': AddToken(TokenType::STAR); break;
		case '!': AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
		case '=': AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
		case '<': AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
		case '>': AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
		case '\n': ++m_Line; break;
		default:
			ErrorReporting::ReportError(std::format("Unexpected character found at line {}", m_Line));
		break;
	}
}

char Scanner::Advance()
{
	assert(m_Current < m_Source.length());

	return m_Source[m_Current++];
}

bool Scanner::Match(char expected)
{
	if (IsAtEnd()) return false;
	if (m_Source.at(m_Current) != expected) return false;

	++m_Current;

	return true;
}

void Scanner::AddToken(TokenType type)
{
	m_Tokens.emplace_back(type, "", m_Line);
}

bool Scanner::IsAtEnd() const
{
	return m_Current >= m_Source.length();
}

void Scanner::PrintTokens() const
{
	for (auto& token : m_Tokens)
	{
		std::cout << token.GetTypeName() << std::endl;
	}
}
