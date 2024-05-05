#include <format>
#include <iostream>

struct Args
{
	int upperBound;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument(
			std::format("Invalid arguments count\nUsage: {} <upper bound>", argv[0]));
	}

	int upperBound;
	try
	{
		upperBound = std::stoi(argv[1]);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument("Invalid  <upper bound> argument");
	}

	return Args(upperBound);
}

int main(int argc, char* argv[])
{
	Args args{};
	try
	{
		args = ParseArgs(argc, argv);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
