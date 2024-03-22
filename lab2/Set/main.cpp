#include "include/SetUtils.h"
#include <format>
#include <iostream>
#include <ctime>

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

void PrintPrimeNumbers(const std::set<int>& primes)
{
	for (auto num : primes) {
		std::cout << num << std::endl;
	}
}

int main(int argc, char* argv[])
{
	Args args{};
	std::set<int> primes{};
	time_t startTime = std::clock();
	try
	{
		args = ParseArgs(argc, argv);
		primes = GeneratePrimeNumbersSet(args.upperBound);
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	auto executionTime = static_cast<double>(std::clock() - startTime) / 1000.0;
	std::string executionTimeString = std::format("Execution time: {}", executionTime);
	std::cout << executionTimeString << std::endl;
	std::cout << std::format("Primes count: {} ", primes.size()) << std::endl;
//	PrintPrimeNumbers(primes);

	return 0;
}
