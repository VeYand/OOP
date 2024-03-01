#include "include/MatrixOperations.h"
#include <array>
#include <format>
#include <iostream>
#include <string>

struct Args
{
	std::string matrixFilePath;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::runtime_error(std::format("Invalid arguments count\nUsage: {} <matrix file>", argv[0]));
	}

	Args args;
	args.matrixFilePath = argv[1];

	return args;
}

void InvertMatrix(const std::string& matrixFilePath)
{
	auto matrix = ReadMatrix(matrixFilePath);
	auto invertedMatrix = InvertMatrix(matrix);

	if (!invertedMatrix.has_value()) {
		std::cout << "The matrix does not have an inverse matrix." << std::endl;
		return;
	}

	PrintMatrix(invertedMatrix.value());
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		InvertMatrix(args.matrixFilePath);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
