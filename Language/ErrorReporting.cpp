#include "ErrorReporting.h"
#include <iostream>	

void ErrorReporting::ReportError(std::string_view error)
{
	std::cerr << error << std::endl;
}
