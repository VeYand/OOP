#include <gtest/gtest.h>
#include "../include/SetUtils.h"

TEST (prime_numbers, less_then_minimal_upper_bound)
{
	EXPECT_THROW(GeneratePrimeNumbersSet(1), std::invalid_argument);
}

TEST (prime_numbers, bigger_then_maximal_upper_bound)
{
	EXPECT_THROW(GeneratePrimeNumbersSet(100000001), std::invalid_argument);
}

TEST (prime_numbers, maximal_upper_boun32)
{
	auto primes = GeneratePrimeNumbersSet(17);
	EXPECT_EQ(7, primes.size());
}

TEST (prime_numbers, maximal_upper_bound12) // на конкретные значения
{
	auto primes = GeneratePrimeNumbersSet(2);
	EXPECT_EQ(1, primes.size());
}

TEST (prime_numbers, maximal_upper_b2ound)
{
	auto primes = GeneratePrimeNumbersSet(100000000 - 1);
	EXPECT_EQ(5761455, primes.size());
}

TEST (prime_numbers, maximal_upper_bound)
{
	auto primes = GeneratePrimeNumbersSet(100000000);
	EXPECT_EQ(5761455, primes.size());
}

GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}