#include "include/ShapeControlService.h"
#include <format>
#include <iostream>

struct Args
{
	std::string inputFileName;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			std::format("Invalid arguments count\nUsage: {} <input_file_name>", argv[0]));
	}

	return Args(argv[1]);
}

int main(int argc, char* argv[])
{
	Args args{};
	ShapeControlService shapeService;

	try
	{
		args = ParseArgs(argc, argv);
		shapeService.ReadShapes(args.inputFileName);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	shapeService.PrintShapeWithMaxAreaInfo();
	shapeService.PrintShapeWithMinPerimeterInfo();

	return 0;
}
