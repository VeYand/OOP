#include "include/CanvasWindowControlService.h"
#include <format>
#include <fstream>
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
	CanvasWindowControlService shapeService;

	try
	{
		args = ParseArgs(argc, argv);
		if (args.inputFileName.has_value())
		{
			std::ifstream file(args.inputFileName.value());
			shapeService.DrawShapes(file);
		}
		else
		{
			shapeService.DrawShapes(std::cin);
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

	return 0;
}
