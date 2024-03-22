#include "include/ExpandTemplate.h"
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	Replacement params;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		throw std::invalid_argument(std::format("Invalid arguments count\n"
												"Usage: {} <input file> <output file> [<param> <value> [<param> <value> Е]]",
			argv[0]));
	}

	Replacement params;
	for (int i = 4; i < argc; i += 2)
	{
		params[argv[i - 1]] = argv[i];
	}

	return Args(argv[1], argv[2], params);
}

void CopyStreamsWithReplacement(std::ifstream& inputFile, std::ofstream& outputFile, const Replacement& params)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		outputFile << ExpandTemplate(line, params) << std::endl; // TODO каждый раз происходит постройка дерева бора заново

		if (!outputFile.flush())
		{
			throw std::runtime_error("Failed to save data on disk");
		}
	}

	if (!inputFile.eof())
	{
		throw std::runtime_error("Error reading input file");
	}
}

void CopyFilesWithReplacement(const std::string& inputFilePath, const std::string& outputFilePath, const Replacement& params)
{
	std::ifstream inputFile(inputFilePath);
	std::ofstream outputFile(outputFilePath);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFilePath + " for reading");
	}

	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFilePath + " for writing");
	}

	CopyStreamsWithReplacement(inputFile, outputFile, params);
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	try
	{
		auto args = ParseArgs(argc, argv);
		CopyFilesWithReplacement(args.inputFileName, args.outputFileName, args.params);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}