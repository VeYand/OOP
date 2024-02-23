#include <cmath>
#include <format>
#include <iostream>
#include <string>

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

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
		throw std::runtime_error(std::format("Invalid arguments count\nUsage: {} <source notation> <destination notation> <value>", argv[0]));
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

	if (std::isdigit(alpha) && (alpha < '0' + radix))
	{
		return alpha - '0';
	}
	if (std::isalpha(alpha))
	{
		int upperAlpha = std::toupper(alpha);
		if (upperAlpha < 'A' + radix - 10)
		{
			return upperAlpha - 'A' + 10;
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

	int decimalNumber = 0;
	int offset = 0;
	bool isNegative = false;

	if (str[0] == '-')
	{
		isNegative = true;
		offset = 1;
	}

	for (size_t i = 0; i < str.length() - offset; ++i)
	{
		auto alpha = AlphaToInt(str[str.length() - i - 1], radix);
		if (decimalNumber > (std::numeric_limits<int>::max() - alpha * (int)std::pow(radix, i)))
		{
			throw std::overflow_error("Overflow during conversion");
		}
		decimalNumber += alpha * (int)std::pow(radix, i);
	}

	if (isNegative)
	{
		decimalNumber *= -1;
	}

	return decimalNumber;
}

char IntToAlpha(int n)
{
	if (n > MAX_RADIX || n < 0)
	{
		throw std::invalid_argument(std::format("Number out of range [0, {}]", MAX_RADIX));
	}

	if (n < 10)
	{
		return static_cast<char>('0' + n);
	}

	return static_cast<char>('A' + (n - 10));
}

std::string IntToString(int n, int radix)
{
	if (radix > MAX_RADIX || radix < MIN_RADIX)
	{
		throw std::invalid_argument(std::format("Radix out of range [{}, {}]", MIN_RADIX, MAX_RADIX));
	}

	std::string result;

	if (n == 0)
	{
		return "0";
	}

	bool isNegative = false;
	if (n < 0)
	{
		isNegative = true;
		n = -n;
	}

	while (n > 0)
	{
		int remainder = n % radix;
		char digit = IntToAlpha(remainder);
		result.insert(result.begin(), digit);
		n /= radix;
	}

	if (isNegative)
	{
		result.insert(result.begin(), '-');
	}

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
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
