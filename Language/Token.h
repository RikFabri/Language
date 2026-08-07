#pragma once
#include <string>
#include <string_view>

enum class TokenType
{
	// Single-character tokens.
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals.
	IDENTIFIER, STRING, NUMBER,

	// Keywords.
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	EOD // EOF is already in use
};

class Token
{
public:
	Token(TokenType type, std::string_view lexeme, int line);

	std::string_view GetTypeName() const;

	static std::string_view GetTokenTypeName(TokenType type);
private:
	TokenType m_TokenType;
	std::string m_Lexeme;
	int m_Line;
};

