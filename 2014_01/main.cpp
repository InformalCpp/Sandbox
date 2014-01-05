#include <iostream>

#include "Units.h"

#include "Testing.h"

extern TestContainer makeTests();

int main(int argc, char ** argv)
{
	for (auto test : makeTests()) 
	{
		try
		{
			test.second();
			std::cout << "Pass: " << test.first << std::endl;
		}
		catch (std::string const& str)
		{
			std::cout << "Fail: " << test.first << ": " << str << std::endl;
		}
	}
	return 0;
}
