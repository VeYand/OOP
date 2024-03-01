#include "include/MapUtilities.h"
#include <format>
#include <iostream>
#include <vector>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		throw std::invalid_argument(
			std::format("Invalid arguments count\nUsage: {} <input file> <output file>", argv[0]));
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		FillMap(args.inputFileName, args.outputFileName);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
