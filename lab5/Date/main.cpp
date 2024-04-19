#include "include/CDate.h"
#include <format>
#include <iostream>

int main(int argc, char* argv[])
{
	auto date = CDate();

	while (true)
	{
		try
		{
			std::cin >> date;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
		}

		std::cout << date << std::endl;
	}

	return 0;
}
