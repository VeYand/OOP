#include "../include/StringUtils.h"
#include <algorithm>
#include <stdexcept>

const std::string WHITESPACE = " \n\r\t\f\v";

void Trim(std::string& str)
{
	size_t start = str.find_first_not_of(WHITESPACE);
	size_t end = str.find_last_not_of(WHITESPACE);

	if (start != std::string::npos && end != std::string::npos)
	{
		str = str.substr(start, end - start + 1);
		return;
	}

	if (start != std::string::npos && end == std::string::npos)
	{
		str = str.substr(start);
		return;
	}

	if (start == std::string::npos && end != std::string::npos)
	{
		str = str.substr(0, end + 1);
	}
}

void Lower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

int StringToInt(const std::string& str)
{
	int number;
	try
	{
		number = std::stoi(str);
	}
	catch (const std::exception& e)
	{
		throw std::invalid_argument("Invalid number");
	}
	return number;
}