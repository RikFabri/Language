#include <iostream>
#include "Scanner.h"

int main()
{
	Scanner scanner{
		"int a = 5 + 6 \
		a += 1"
	};

	scanner.ScanTokens();
	scanner.PrintTokens();

	return 0;
}