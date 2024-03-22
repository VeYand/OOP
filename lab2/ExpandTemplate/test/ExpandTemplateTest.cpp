#include "../include/ExpandTemplate.h"
#include <gtest/gtest.h>

TEST(ExpandTemplateTest, test1)
{
	std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
	std::map<std::string, std::string> params;
	params["%USER_NAME%"] = "Ivan Petrov";
	params["{WEEK_DAY}"] = "Friday";
	EXPECT_EQ(ExpandTemplate(tpl, params), "Hello, Ivan Petrov. Today is Friday.");
}

TEST(ExpandTemplateTest, test2)
{
	std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
	std::map<std::string, std::string> params;
	params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
	params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
	EXPECT_EQ(ExpandTemplate(tpl, params),
		"Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
}

TEST(ExpandTemplateTest, test3)
{
	std::string const tpl = "-AABBCCCCCABC+";
	std::map<std::string, std::string> params;
	params["A"] = "[a]";
	params["AA"] = "[aa]";
	params["B"] = "[b]";
	params["BB"] = "[bb]";
	params["C"] = "[c]";
	params["CC"] = "[cc]";
	EXPECT_EQ(ExpandTemplate(tpl, params),
		"-[aa][bb][cc][cc][c][a][b][c]+");
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}