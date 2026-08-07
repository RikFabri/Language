#include "Scanner.h"
#include <iostream>
#include <cassert>
#include "ErrorReporting.h"
#include <unordered_map>


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
		case '/': if (Match('/')) { HandleComment(); } else { AddToken(TokenType::SLASH); } break;
		case '"': HandleString(); break;
		
		case ' ':
		case '\r':
		case '\t':
			break;
		
		case '\n': ++m_Line; break;
		default:
			if (isdigit(c))
			{
				HandleNumber();
			}
			else if (isalpha(c))
			{
				HandleIdentifier();
			}
			else
			{
				Error("Unexpected character found");
			}
		break;
	}
}

char Scanner::Advance()
{
	assert(m_Current < m_Source.length());

	return m_Source[m_Current++];
}

char Scanner::Peek() const
{
	if (IsAtEnd()) return '\0';
	return m_Source.at(m_Current);
}

char Scanner::PeekNext(unsigned offset) const
{
	if (m_Current + offset >= m_Source.length()) return '\0';
	return m_Source.at(m_Current + offset);
}

bool Scanner::Match(char expected)
{
	if (IsAtEnd()) return false;
	if (m_Source.at(m_Current) != expected) return false;

	++m_Current;

	return true;
}

std::string_view Scanner::GetCurrentLexeme() const
{
	return m_Source.substr(m_Start, m_Current - m_Start);
}

void Scanner::AddToken(TokenType type, std::string_view value)
{
	m_Tokens.emplace_back(type, value, m_Line);
}

void Scanner::Error(std::string_view error)
{
	ErrorReporting::ReportError(std::format("{} <-- line {}", error, m_Line));
}

void Scanner::HandleComment()
{
	while (Peek() != '\n' && !IsAtEnd())
	{
		Advance();
	}
}

void Scanner::HandleString()
{
	while (Peek() != '"' && !IsAtEnd())
	{
		if (Peek() == '\n') ++m_Line;

		Advance();

		if (IsAtEnd())
		{
			ErrorReporting::ReportError("Unterminated string");
			return;
		}

	}
	Advance();

	AddToken(TokenType::STRING, GetCurrentLexeme());
}

void Scanner::HandleNumber()
{
	while (isdigit(Peek())) Advance();

	if (Peek() == '.' && isdigit(PeekNext()))
	{
		while (isdigit(Peek())) Advance();
	}

	AddToken(TokenType::NUMBER, GetCurrentLexeme());
}

void Scanner::HandleIdentifier()
{
	while (IsAlphaNumeric(Peek())) Advance();

	const auto lexeme = GetCurrentLexeme();
	const auto tokenType = GetReservedKeywordOrIdentifier(lexeme);

	AddToken(tokenType, lexeme);
}

TokenType Scanner::GetReservedKeywordOrIdentifier(std::string_view lexeme)
{
	std::unordered_map<std::string_view, TokenType> reservedKeywords{
		{ "and",    TokenType::AND},
		{ "class",  TokenType::CLASS},
		{ "else",   TokenType::ELSE},
		{ "false",  TokenType::FALSE},
		{ "for",    TokenType::FOR},
		{ "fun",    TokenType::FUN},
		{ "if",     TokenType::IF},
		{ "nil",    TokenType::NIL},
		{ "or",     TokenType::OR},
		{ "print",  TokenType::PRINT},
		{ "return", TokenType::RETURN},
		{ "super",  TokenType::SUPER},
		{ "this",   TokenType::THIS},
		{ "true",   TokenType::TRUE},
		{ "var",    TokenType::VAR},
		{ "while",  TokenType::WHILE }
	};

	if (!reservedKeywords.contains(lexeme))
		return TokenType::IDENTIFIER;

	return reservedKeywords.at(lexeme);
}

bool Scanner::IsAlphaNumeric(char c)
{
	return isalpha(c) || isdigit(c);
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
