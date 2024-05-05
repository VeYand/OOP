#include "../include/CMyString.h"
#include <gtest/gtest.h>

TEST(CMyString, DefaultConstructor)
{
	CMyString str;
	EXPECT_EQ(str.GetLength(), 0);
	EXPECT_STREQ(str.GetStringData(), "");
}

TEST(CMyString, ConstructorFromString)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_EQ(str.GetLength(), 11);
	EXPECT_STREQ(str.GetStringData(), "Test String");
}

TEST(CMyString, ConstructorFromStringWithLength)
{
	const char* testData = "Test String";
	size_t length = 4;
	CMyString str(testData, length);
	EXPECT_EQ(str.GetLength(), length);
	EXPECT_STREQ(str.GetStringData(), "Test");
}

TEST(CMyString, CopyConstructor)
{
	const char* testData = "Test String";
	CMyString original(testData);
	CMyString copy(original);
	EXPECT_EQ(copy.GetLength(), original.GetLength());
	EXPECT_EQ(copy.GetLength(), 11);
	EXPECT_STREQ(copy.GetStringData(), original.GetStringData());
	EXPECT_STREQ(copy.GetStringData(),"Test String");
}

TEST(CMyString, MoveConstructor)
{
	const char* testData = "Test String";
	CMyString original(testData);
	CMyString moved(std::move(original));
	EXPECT_EQ(moved.GetLength(), 11);
	EXPECT_STREQ(moved.GetStringData(), "Test String");
	EXPECT_EQ(original.GetLength(), 0);
	EXPECT_EQ(original.GetStringData(), nullptr);
}

TEST(CMyString, ConstructorFromStdString)
{
	std::string testData = "Test String";
	CMyString str(testData);
	EXPECT_EQ(str.GetLength(), 11);
	EXPECT_STREQ(str.GetStringData(), "Test String");
}

TEST(CMyString, GetLength)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_EQ(str.GetLength(), 11);
}

TEST(CMyString, GetStringData)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_STREQ(str.GetStringData(), "Test String");
}

TEST(CMyString, SubString)
{
	const char* testData = "Test String";
	CMyString str(testData);
	CMyString subStr = str.SubString(5, 6);
	EXPECT_EQ(subStr.GetLength(), 6);
	EXPECT_STREQ(subStr.GetStringData(), "String");
}

TEST(CMyString, SubStringOutOfRange)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_THROW(str.SubString(20), std::out_of_range);
}

TEST(CMyString, Clear)
{
	const char* testData = "Test String";
	CMyString str(testData);
	str.Clear();
	EXPECT_EQ(str.GetLength(), 0);
	EXPECT_STREQ(str.GetStringData(), "");
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
