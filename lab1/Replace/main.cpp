#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::runtime_error(std::format("Usage: {} <input file> <output file> <search string> <replace string>", argv[0]));
	}

	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];

	return args;
}

std::string ReplaceString(const std::string& subject, const std::string& searchString,
	const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;

	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		if (foundPos == std::string::npos)
		{
			result.append(subject, pos);
			return result;
		}

		result.append(subject, pos, foundPos - pos);
		result.append(replacementString);
		pos = foundPos + searchString.length();
	}
	return result;
}

void CopyStreamsWithReplacement(std::ifstream& inputFile, std::ofstream& outputFile,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;
	while (std::getline(inputFile, line))
	{
		outputFile << ReplaceString(line, searchString, replacementString) << std::endl;
	}

	if (!inputFile.eof())
	{
		throw std::runtime_error("Error reading input file");
	}
}

void CopyFilesWithReplacement(const std::string& inputFilePath, const std::string& outputFilePath,
	const std::string& searchString, const std::string& replacementString)
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

	CopyStreamsWithReplacement(inputFile, outputFile, searchString, replacementString);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		CopyFilesWithReplacement(args.inputFileName, args.outputFileName, args.searchString, args.replaceString);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
