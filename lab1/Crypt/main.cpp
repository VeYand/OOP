#include "include/CryptTools.h"
#include <format>
#include <iostream>

enum class Mode
{
	CRYPT,
	DECRYPT
};

struct Args
{
	Mode mode{};
	std::string inputFileName;
	std::string outputFileName;
	int key{};
};

Mode ParseMode(const std::string& modeStr)
{
	if (modeStr == "crypt")
	{
		return Mode::CRYPT;
	}
	else if (modeStr == "decrypt")
	{
		return Mode::DECRYPT;
	}
	else
	{
		throw std::invalid_argument("Invalid mode. Use 'crypt' or 'decrypt'.");
	}
}

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument(
			std::format("Invalid arguments count\nUsage: {}  crypt|decrypt <input file> <output file> <key>", argv[0]));
	}

	Args args;
	args.mode = ParseMode(argv[1]);
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	try
	{
		args.key = std::stoi(argv[4]);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument("Invalid crypt key");
	}

	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		if (args.mode == Mode::CRYPT)
		{
			Crypt(args.inputFileName, args.outputFileName, args.key);
		}
		else
		{
			Decrypt(args.inputFileName, args.outputFileName, args.key);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}