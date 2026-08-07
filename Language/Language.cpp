#include <iostream>
#include "Scanner.h"

int main()
{
	Scanner scanner{
		//"\"hello\"+"
		"#include \"Scanner.h\"\n \
		\n \
		int main()\n \
		{   while 10.5\n \
			Scanner scanner{};\n \
			scanner.ScanTokens();\n \
			scanner.PrintTokens();\n \
				\n \
			return 0;\n \
		}"
	};

	scanner.ScanTokens();
	scanner.PrintTokens();

	return 0;
}