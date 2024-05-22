#include "../include/Athlete.h"
#include "../include/FindMaxEx.h"
#include <gtest/gtest.h>

TEST(FindMaxExTest, FindMaxHeight) {
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

TEST(FindMaxExTest, FindMaxWeight) {
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

TEST(FindMaxExTest, EmptyVector) {
	std::vector<Athlete> athletes{};

	Athlete result;
	ASSERT_FALSE(FindMaxEx(athletes, result, [](const Athlete& a, const Athlete& b) {
		return a.height < b.height;
	}));

	EXPECT_EQ(result.name, "");
	EXPECT_EQ(result.height, 0);
	EXPECT_EQ(result.weight, 0);
}

GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}