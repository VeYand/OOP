#include "../include/VectorOperations.h"
#include <gtest/gtest.h>
#include <cmath>

double GetAbsError(double number)
{
	auto numberString = std::to_string(number);
	auto dotPos = numberString.find_last_of('.');
	if (dotPos == std::string::npos) {
		return 0;
	}

	auto lastNonZero = numberString.find_last_not_of('0');
	if (lastNonZero != std::string::npos && lastNonZero > dotPos) {
		numberString.erase(lastNonZero + 1);
	}

	auto decimalPart = numberString.substr(dotPos + 1);
	if (decimalPart.empty()) {
		return 0;
	}

	auto error = std::pow(10, -1 * static_cast<double>(decimalPart.length()));

	return error;
}

TEST (perform_operation, positive_and_negative_elements)
{
	std::vector<double> numbers = {1, -2, 2, 3, 4, -9};
	std::vector<double> expectedResult = {1, 72, 2, 3, 4, 324};

	MultiplyNegativeNumsToMaxAndMinNum(numbers);
	for (size_t i = 0; i < expectedResult.size(); ++i)
	{
		EXPECT_EQ(expectedResult[i], numbers[i]);
	}
}

TEST (perform_operation, positive_elements)
{
	std::vector<double> numbers = {1, 2, 2, 3, 4, 9};
	std::vector<double> expectedResult = {1, 2, 2, 3, 4, 9};

	MultiplyNegativeNumsToMaxAndMinNum(numbers);
	for (size_t i = 0; i < expectedResult.size(); ++i)
	{
		EXPECT_EQ(expectedResult[i], numbers[i]);
	}
}

TEST (perform_operation, negative_elements)
{
	std::vector<double> numbers = {-1, -2, -2, -3, -4, -9};
	std::vector<double> expectedResult = {-9, -18, -18, -27, -36, -81};

	MultiplyNegativeNumsToMaxAndMinNum(numbers);
	for (size_t i = 0; i < expectedResult.size(); ++i)
	{
		EXPECT_EQ(expectedResult[i], numbers[i]);
	}
}

TEST (perform_operation, positive_and_negative_double_numbers)
{
	std::vector<double> numbers = {1.3, -2.9, 2.1};
	std::vector<double> expectedResult = {1.3, 17.661, 2.1};

	MultiplyNegativeNumsToMaxAndMinNum(numbers);
	for (size_t i = 0; i < expectedResult.size(); ++i)
	{
		EXPECT_NEAR(expectedResult[i], numbers[i], GetAbsError(expectedResult[i]));
	}
}

TEST (perform_operation, empty_vector)
{
	std::vector<double> numbers;

	MultiplyNegativeNumsToMaxAndMinNum(numbers);

	EXPECT_TRUE(numbers.empty());
}

TEST (sort, empty_vector)
{
	std::vector<double> numbers;

	Sort(numbers);

	EXPECT_TRUE(numbers.empty());
}

TEST (sort, some_double_numbers)
{
	std::vector<double> numbers = {1.333, -2.9991, 2.1231};
	std::vector<double> expectedResult = {-2.9991, 1.333, 2.1231};

	Sort(numbers);

	for (size_t i = 0; i < expectedResult.size(); ++i)
	{
		EXPECT_EQ(expectedResult[i], numbers[i]);
	}
}

GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}