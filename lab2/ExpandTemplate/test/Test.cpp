#include <gtest/gtest.h>

TEST (test_name, test_description)
{
	EXPECT_EQ(true, true);
}

GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}