#include "include/ShapeControlService.h"
#include <format>
#include <iostream>

struct Args
{
	std::optional<std::string> inputFileName;
};

Args ParseArgs(int argc, char* argv[])
{
	std::optional<std::string> inputFileName = std::nullopt;

	if (argc >= 2)
	{
		inputFileName = argv[1];
	}

	return Args(inputFileName);
}

int main(int argc, char* argv[])
{
	Args args{};
	ShapeControlService shapeService;

	try
	{
		args = ParseArgs(argc, argv);
		if (args.inputFileName.has_value())
		{
			shapeService.ReadShapes(args.inputFileName.value());
		}
		else
		{
			shapeService.ReadShapes(std::cin);
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	shapeService.PrintShapeWithMaxAreaInfo();
	shapeService.PrintShapeWithMinPerimeterInfo();

	return 0;
}
