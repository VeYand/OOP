#include "../include/Athlete.h"
#include "../include/FindMaxEx.h"
#include <gtest/gtest.h>

TEST(FindMaxExTest, FindMaxHeight)
{
	std::vector<Athlete> athletes = {
		{ "Bob Johnson", 180, 75 },
		{ "Carey Mulligan", 170, 60 },
		{ "Ryan Gosling", 190, 85 },
		{ "Christina Hendricks", 175, 65 }
	};

	Athlete tallest;
	ASSERT_TRUE(FindMaxEx(athletes, tallest, [](const Athlete& a, const Athlete& b) {
		return a.height < b.height;
	}));

	EXPECT_EQ(tallest.name, "Ryan Gosling");
	EXPECT_EQ(tallest.height, 190);
	EXPECT_EQ(tallest.weight, 85);
}

TEST(FindMaxExTest, FindMaxWeight)
{
	std::vector<Athlete> athletes = {
		{ "Bob Johnson", 180, 75 },
		{ "Carey Mulligan", 170, 60 },
		{ "Ryan Gosling", 190, 85 },
		{ "Christina Hendricks", 175, 65 }
	};

	Athlete heaviest;
	ASSERT_TRUE(FindMaxEx(athletes, heaviest, [](const Athlete& a, const Athlete& b) {
		return a.weight < b.weight;
	}));

	EXPECT_EQ(heaviest.name, "Ryan Gosling");
	EXPECT_EQ(heaviest.height, 190);
	EXPECT_EQ(heaviest.weight, 85);
}

TEST(FindMaxExTest, EmptyVector)
{
	std::vector<Athlete> athletes{};

	Athlete result;
	ASSERT_FALSE(FindMaxEx(athletes, result, [](const Athlete& a, const Athlete& b) {
		return a.height < b.height;
	}));

	EXPECT_EQ(result.name, "");
	EXPECT_EQ(result.height, 0);
	EXPECT_EQ(result.weight, 0);
}

TEST(FindMaxExTest, OneValueInVector)
{
	std::vector<int> nums = { -999 };

	int max;
	ASSERT_TRUE(FindMaxEx(nums, max, [](const int& a, const int& b) {
		return a < b;
	}));

	EXPECT_EQ(max, -999);
}

TEST(FindMaxExTest, FindMaxInteger)
{
	std::vector<int> nums = { -999, -1, 0, 1, 2, 5, 9 };

	int max;
	ASSERT_TRUE(FindMaxEx(nums, max, [](const int& a, const int& b) {
		return a < b;
	}));

	EXPECT_EQ(max, 9);
}

TEST(FindMaxExTest, FindMaxDouble)
{
	std::vector<double> nums = { -999.0, -1.0, 0.0, 1.0, 2.0, 5.0, 9.0, 9.1 };

	double max;
	ASSERT_TRUE(FindMaxEx(nums, max, [](const double& a, const double& b) {
		return a < b;
	}));

	EXPECT_EQ(max, 9.1);
}

TEST(FindMaxExTest, FindMaxString)
{
	std::vector<std::string> strings = { "", "ab", "aa", "a" };

	std::string max;
	ASSERT_TRUE(FindMaxEx(strings, max, [](const std::string& a, const std::string& b) {
		return a < b;
	}));

	EXPECT_EQ(max, "ab");
}

TEST(FindMaxExTest, ExceptionInFunction)
{
	std::vector<int> nums = { -999, -1, 0, 1, 2, 5, 9 };

	int max = 10;
	int count = 0;
	EXPECT_THROW(FindMaxEx(nums, max, [&](const int& a, const int& b) {
		count++;
		if (count == 2)
		{
			throw std::runtime_error("Test exception");
		}
		return a < b;
	}), std::runtime_error);

	EXPECT_EQ(max, 10);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}