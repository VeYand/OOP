#include "../include/SetUtils.h"
#include <format>
#include <vector>

const int MAX_NUMBER = 100'000'000;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
 	if (upperBound < 2 || upperBound > MAX_NUMBER)
	{
		throw std::invalid_argument(std::format("Upper bound must be less then {} and upper then 1", MAX_NUMBER));
	}

	std::vector<bool> isPrime(upperBound + 1, true);

	std::set<int> primeNumbers;

	isPrime[0] = isPrime[1] = false;
	primeNumbers.insert(2);

	for (int p = 3; p <= upperBound; p += 2)
	{
		if (isPrime[p])
		{
			primeNumbers.insert(primeNumbers.end(), p);
			for (int i = 2 * p + p; i <= upperBound; i += 2 * p)
			{
				isPrime[i] = false;
			}
		}
	}

	return primeNumbers;
}