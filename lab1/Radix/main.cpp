#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <string>

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const char NEGATIVE_SYMBOL = '-';
const char FIRST_CHAR_DIGIT = '0';
const char FIRST_CHAR_LETTER = 'A';

struct Args
{
	int sourceNotation{};
	int destinationNotation{};
	std::string value;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::runtime_error(std::format("Invalid arguments count\n"
											 "Usage: {} <source notation> <destination notation> <value>",
			argv[0]));
	}

	Args args;
	try
	{
		args.sourceNotation = std::stoi(argv[1]);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(std::format("Invalid source notation: {}", e.what()));
	}

	try
	{
		args.destinationNotation = std::stoi(argv[2]);
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(std::format("Invalid destination notation: {}", e.what()));
	}

	args.value = argv[3];

	return args;
}

int AlphaToInt(const char& alpha, int radix)
{
	if (radix > MAX_RADIX || radix < MIN_RADIX)
	{
		throw std::invalid_argument(std::format("Radix out of range [{}, {}]", MIN_RADIX, MAX_RADIX));
	}

	if (std::isdigit(alpha) && (alpha < FIRST_CHAR_DIGIT + radix))
	{
		return alpha - FIRST_CHAR_DIGIT;
	}
	if (std::isalpha(alpha))
	{
		int upperAlpha = std::toupper(alpha);
		if (upperAlpha < FIRST_CHAR_LETTER + radix - 10)
		{
			return upperAlpha - FIRST_CHAR_LETTER + 10;
		}
	}

	throw std::runtime_error(std::format("Invalid input character for the given radix {}", alpha));
}

int StringToInt(const std::string& str, int radix)
{
	if (radix > MAX_RADIX || radix < MIN_RADIX)
	{
		throw std::invalid_argument(std::format("Radix out of range [{}, {}]", MIN_RADIX, MAX_RADIX));
	}

	if (str.empty())
	{
		throw std::invalid_argument("Invalid input string");
	}

	int number = 0;
	int sign = 1;
	for (const auto& ch : str)
	{
		if (ch == NEGATIVE_SYMBOL)
		{
			if (ch != str[0])
			{
				throw std::invalid_argument("Invalid input string");
			}

			sign *= -1;
			continue;
		}

		auto alpha = AlphaToInt(ch, radix);

		if (
			(number * sign) < (std::numeric_limits<int>::min() + alpha) / radix
			|| sign > 0 && number > (std::numeric_limits<int>::max() - alpha) / radix)
		{
			throw std::runtime_error("Invalid max value in integer");
		}

		number = number * radix + alpha;
	}

	return number * sign;
}

char IntToAlpha(int n)
{
	if (n > MAX_RADIX || n < 0)
	{
		throw std::invalid_argument(std::format("Number out of range [0, {}]", MAX_RADIX));
	}

	if (n < 10)
	{
		return static_cast<char>(FIRST_CHAR_DIGIT + n);
	}

	return static_cast<char>(FIRST_CHAR_LETTER + (n - 10));
}

std::string IntToString(int n, int radix)
{
	if (radix > MAX_RADIX || radix < MIN_RADIX)
	{
		throw std::invalid_argument(std::format("Radix out of range [{}, {}]", MIN_RADIX, MAX_RADIX));
	}

	auto isNegative = n < 0;

	std::string result;
	do
	{
		int remainder = n % radix;
		char digit = IntToAlpha(std::abs(remainder));
		result += digit;
		n /= radix;
	} while (n != 0);

	if (isNegative)
	{
		result += NEGATIVE_SYMBOL;
	}

	std::reverse(result.begin(), result.end());
	return result;
}

std::string ChangeRadix(int sourceNotation, int destinationNotation, const std::string& value)
{
	int decimalValue = StringToInt(value, sourceNotation);
	std::string result = IntToString(decimalValue, destinationNotation);
	return result;
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);
		std::cout << ChangeRadix(args.sourceNotation, args.destinationNotation, args.value) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
