#include "include/Dictionary.h"
#include <format>
#include <iostream>
#include <stdexcept>
#include <windows.h>

struct Args
{
	std::string inputFileName;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			std::format("Invalid arguments count\nUsage: {} <input file>", argv[0]));
	}

	return Args(argv[1]);
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Args args;
	try
	{
		args = ParseArgs(argc, argv);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	RunDictionary(args.inputFileName);

	return 0;
}
