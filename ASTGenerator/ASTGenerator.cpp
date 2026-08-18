#include <iostream>
#include <string_view>
#include <fstream>
#include <ranges>

void WriteType(std::ofstream& file, std::string_view className, std::string_view fields)
{
	file << std::format("struct {}: public Expression\n{{\n\t{}(", className, className);
	file << fields;
	file << std::format("){{}}\n");

	for (const auto field : std::views::split(fields, std::string_view{ ", " }))
	{
		file << std::string_view{ field } << ";\n";
	}

	file << "};";
}

int GenerateAST(std::string_view description)
{
	std::ofstream file{ "AstNodes.h" };
	if (!file) return 1;

	file << "#pragma once\n";
	file << "#include \"Token.h\"\n\n";
	file << "struct Expression{};\n\n";

	for (const auto production : std::views::split(description, '\n'))
	{
		const std::string_view line{ production };

		const auto offset = line.find(':');
		const std::string_view className = line.substr(0, offset);
		const std::string_view fields = line.substr(offset + 1);

		WriteType(file, className, fields);
	}

	return 0;
}

int main(int argc, char* argv[])
{
	return GenerateAST(
		"Binary : Expression left, Token* operator, Expression right\n" \
		"Grouping : Expression expression\n" \
		"Literal : std::Any value\n" \
		"Unary : Token* operator, Expression right\n");
}