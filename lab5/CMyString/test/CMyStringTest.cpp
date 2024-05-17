#include "../include/CMyString.h"
#include <gtest/gtest.h>

TEST(CMyString, DefaultConstructor)
{
	CMyString str;
	EXPECT_EQ(str.GetLength(), 0);
	EXPECT_STREQ(str.GetStringData(), "");
	EXPECT_EQ(str.GetCapacity(), 1);
}

TEST(CMyString, ConstructorFromString)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_EQ(str.GetLength(), 11);
	EXPECT_STREQ(str.GetStringData(), "Test String");
	EXPECT_GE(str.GetCapacity(), 12);
}

TEST(CMyString, ConstructorFromStringWithLength)
{
	const char* testData = "Test String";
	size_t length = 4;
	CMyString str(testData, length);
	EXPECT_EQ(str.GetLength(), length);
	EXPECT_STREQ(str.GetStringData(), "Test");
	EXPECT_GE(str.GetCapacity(), length + 1);
}

TEST(CMyString, CopyConstructor)
{
	const char* testData = "Test String";
	CMyString original(testData);
	CMyString copy(original);
	EXPECT_EQ(copy.GetLength(), original.GetLength());
	EXPECT_EQ(copy.GetLength(), 11);
	EXPECT_STREQ(copy.GetStringData(), original.GetStringData());
	EXPECT_STREQ(copy.GetStringData(), "Test String");
	EXPECT_GE(copy.GetCapacity(), 12);
}

TEST(CMyString, MoveConstructor)
{
	const char* testData = "Test String";
	CMyString original(testData);
	CMyString moved(std::move(original));
	EXPECT_EQ(moved.GetLength(), 11);
	EXPECT_STREQ(moved.GetStringData(), "Test String");
	EXPECT_GE(moved.GetCapacity(), 12);
	EXPECT_EQ(original.GetLength(), 0);
	EXPECT_STREQ(original.GetStringData(), "");
	EXPECT_EQ(original.GetCapacity(), 1);
}

TEST(CMyString, ConstructorFromStdString)
{
	std::string testData = "Test String";
	CMyString str(testData);
	EXPECT_EQ(str.GetLength(), 11);
	EXPECT_STREQ(str.GetStringData(), "Test String");
	EXPECT_GE(str.GetCapacity(), 12);
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

TEST(CMyString, GetCapacity)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_GE(str.GetCapacity(), 12);
}

TEST(CMyString, SubString)
{
	const char* testData = "Test String";
	CMyString str(testData);
	CMyString subStr = str.SubString(5, 6);
	EXPECT_EQ(subStr.GetLength(), 6);
	EXPECT_STREQ(subStr.GetStringData(), "String");
	EXPECT_GE(subStr.GetCapacity(), 7);
}

TEST(CMyString, SubStringOutOfRange)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_THROW(str.SubString(20, 5), std::out_of_range);
}

TEST(CMyString, ClearEmptyString)
{
	CMyString str;
	str.Clear();
	EXPECT_EQ(str.GetLength(), 0);
	EXPECT_STREQ(str.GetStringData(), "");
	EXPECT_EQ(str.GetCapacity(), 1);
}

TEST(CMyString, ClearNotEmptyString)
{
	const char* testData = "Test String";
	CMyString str(testData);
	str.Clear();
	EXPECT_EQ(str.GetLength(), 0);
	EXPECT_STREQ(str.GetStringData(), "");
	EXPECT_EQ(str.GetCapacity(), 1);
}

TEST(CMyString, AssigmentOperation)
{
	CMyString str("Test String");
	{
		auto newStr = str;
		EXPECT_EQ(newStr.GetLength(), 11);
		EXPECT_STREQ(newStr.GetStringData(), "Test String");
		EXPECT_GE(newStr.GetCapacity(), 12);
		newStr.Clear();
		EXPECT_EQ(newStr.GetLength(), 0);
		EXPECT_STREQ(newStr.GetStringData(), "");
		EXPECT_EQ(newStr.GetCapacity(), 1);
	}

	EXPECT_EQ(str.GetLength(), 11);
	EXPECT_STREQ(str.GetStringData(), "Test String");
	EXPECT_GE(str.GetCapacity(), 12);
}

TEST(CMyString, SelfAssigmentOperation)
{
	CMyString str("Test String");

	str = str;

	EXPECT_EQ(str.GetLength(), 11);
	EXPECT_STREQ(str.GetStringData(), "Test String");
	EXPECT_GE(str.GetCapacity(), 12);
	str.Clear();
	EXPECT_EQ(str.GetLength(), 0);
	EXPECT_STREQ(str.GetStringData(), "");
	EXPECT_EQ(str.GetCapacity(), 1);
}

TEST(CMyString, MoveOperation)
{
	const char* testData = "Test String";
	CMyString original(testData);
	CMyString moved = std::move(original);
	EXPECT_EQ(moved.GetLength(), 11);
	EXPECT_STREQ(moved.GetStringData(), "Test String");
	EXPECT_GE(moved.GetCapacity(), 12);
	EXPECT_EQ(original.GetLength(), 0);
	EXPECT_STREQ(original.GetStringData(), "");
	EXPECT_EQ(original.GetCapacity(), 1);
}

TEST(CMyString, OperatorPlusEqualsEmptyString)
{
	CMyString str1;
	CMyString str2("Test");
	str1 += str2;
	EXPECT_EQ(str1.GetLength(), 4);
	EXPECT_STREQ(str1.GetStringData(), "Test");
	EXPECT_GE(str1.GetCapacity(), 5);
}

TEST(CMyString, OperatorPlusEqualsNonEmptyString)
{
	CMyString str1("Hello");
	CMyString str2(" World");
	str1 += str2;
	EXPECT_EQ(str1.GetLength(), 11);
	EXPECT_STREQ(str1.GetStringData(), "Hello World");
	EXPECT_GE(str1.GetCapacity(), 12);
}

TEST(CMyString, OperatorPlusEqualsSelfAssignment)
{
	CMyString str("Hello");
	str += str;
	EXPECT_EQ(str.GetLength(), 10);
	EXPECT_STREQ(str.GetStringData(), "HelloHello");
	EXPECT_GE(str.GetCapacity(), 11);
}

TEST(CMyString, OperatorPlusEqualsEmptyAssignment)
{
	CMyString str("Hello");
	CMyString empty;
	str += empty;
	EXPECT_EQ(str.GetLength(), 5);
	EXPECT_STREQ(str.GetStringData(), "Hello");
	EXPECT_GE(str.GetCapacity(), 6);
}

TEST(CMyString, ChainedAssignment)
{
	CMyString str("Hello");
	str += CMyString(", World") += CMyString("!");
	EXPECT_EQ(str.GetLength(), 13);
	EXPECT_STREQ(str.GetStringData(), "Hello, World!");
	EXPECT_GE(str.GetCapacity(), 14);
}

TEST(CMyString, OperatorIndexAccessValidIndex)
{
	const char* testData = "Hello World";
	CMyString str(testData);
	for (size_t i = 0; i < str.GetLength(); ++i)
	{
		EXPECT_EQ(str[i], testData[i]);
	}
}

TEST(CMyString, OperatorIndexAccessOutOfRange)
{
	CMyString str("Test String");
	EXPECT_THROW(str[str.GetLength()], std::out_of_range);
}

TEST(CMyString, OperatorIndexAccessEmptyString)
{
	CMyString str;
	EXPECT_THROW(str[0], std::out_of_range);
}

TEST(CMyString, OperatorIndexAccessMultipleTimes)
{
	const char* testData = "Test String";
	CMyString str(testData);
	EXPECT_EQ(str[0], 'T');
	EXPECT_EQ(str[5], 'S');
	EXPECT_EQ(str[10], 'g');
}

TEST(CMyString, OperatorIndexMutableAccessAndModifyValidIndex)
{
	char testData[] = "Hello World";
	CMyString str(testData);
	str[0] = 'h';
	str[6] = 'w';
	EXPECT_EQ(str[0], 'h');
	EXPECT_EQ(str[6], 'w');
}

TEST(CMyString, OperatorIndexMutableAccessAndModifyOutOfRange)
{
	char testData[] = "Test String";
	CMyString str(testData);
	EXPECT_THROW(str[str.GetLength()] = 'X', std::out_of_range);
}

TEST(CMyString, OperatorIndexMutableAccessAndModifyEmptyString)
{
	CMyString str;
	EXPECT_THROW(str[0] = 'X', std::out_of_range);
}

TEST(CMyString, OperatorIndexMutableAccessAndModifyMultipleTimes)
{
	char testData[] = "Test String";
	CMyString str(testData);
	str[0] = 't';
	str[5] = 's';
	str[10] = '\0';
	EXPECT_EQ(str[0], 't');
	EXPECT_EQ(str[5], 's');
	EXPECT_EQ(str[10], '\0');
}

TEST(CMyString, OperatorPlusCMyStringCMyString)
{
	CMyString str1("Hello");
	CMyString str2(" World");
	CMyString result = str1 + str2;
	EXPECT_EQ(result.GetLength(), 11);
	EXPECT_STREQ(result.GetStringData(), "Hello World");
	EXPECT_GE(result.GetCapacity(), 12);
}

TEST(CMyString, OperatorPlusStdStringCMyString)
{
	std::string stdStr("Hello");
	CMyString str(" World");
	CMyString result = stdStr + str;
	EXPECT_EQ(result.GetLength(), 11);
	EXPECT_STREQ(result.GetStringData(), "Hello World");
	EXPECT_GE(result.GetCapacity(), 12);
}

TEST(CMyString, OperatorPlusCharPtrCMyString)
{
	const char* charPtr = "Hello";
	CMyString str(" World");
	CMyString result = charPtr + str;
	EXPECT_EQ(result.GetLength(), 11);
	EXPECT_STREQ(result.GetStringData(), "Hello World");
	EXPECT_GE(result.GetCapacity(), 12);
}

TEST(CMyString, OperatorPlusCMyStringStdString)
{
	CMyString str("Hello");
	std::string stdStr(" World");
	CMyString result = str + stdStr;
	EXPECT_EQ(result.GetLength(), 11);
	EXPECT_STREQ(result.GetStringData(), "Hello World");
	EXPECT_GE(result.GetCapacity(), 12);
}

TEST(CMyString, OperatorPlusCMyStringCharPtr)
{
	CMyString str("Hello");
	const char* charPtr = " World";
	CMyString result = str + charPtr;
	EXPECT_EQ(result.GetLength(), 11);
	EXPECT_STREQ(result.GetStringData(), "Hello World");
	EXPECT_GE(result.GetCapacity(), 12);
}

TEST(CMyString, PlusEqualsDoublingCapacity)
{
	CMyString str1("Hello");
	size_t initialCapacity = str1.GetCapacity();
	CMyString str2(" World!");

	str1 += str2;

	EXPECT_EQ(str1.GetLength(), 12);
	EXPECT_STREQ(str1.GetStringData(), "Hello World!");
	EXPECT_GE(str1.GetCapacity(), initialCapacity * 2);
}

TEST(CMyString, PlusDoublingCapacity)
{
	CMyString str1("Hello");
	size_t initialCapacity = str1.GetCapacity();
	CMyString str2(" World!");

	CMyString result = str1 + str2;

	EXPECT_EQ(result.GetLength(), 12);
	EXPECT_STREQ(result.GetStringData(), "Hello World!");
	EXPECT_GE(result.GetCapacity(), initialCapacity * 2);
}

TEST(CMyString, PlusEqualsDoublingCapacityWithMultipleConcatenations)
{
	CMyString str1("A");
	size_t initialCapacity = str1.GetCapacity();
	CMyString str2("B");

	for (int i = 0; i < 20; ++i)
	{
		str1 += str2;
	}

	EXPECT_EQ(str1.GetLength(), 21);
	EXPECT_STREQ(str1.GetStringData(), "ABBBBBBBBBBBBBBBBBBBB");
	EXPECT_GE(str1.GetCapacity(), initialCapacity * 2);
}

TEST(CMyString, PlusDoublingCapacityWithMultipleConcatenations)
{
	CMyString str1("A");
	size_t initialCapacity = str1.GetCapacity();
	CMyString str2("B");
	CMyString result = str1;

	for (int i = 0; i < 20; ++i)
	{
		result = result + str2;
	}

	EXPECT_EQ(result.GetLength(), 21);
	EXPECT_STREQ(result.GetStringData(), "ABBBBBBBBBBBBBBBBBBBB");
	EXPECT_GE(result.GetCapacity(), initialCapacity * 2);
}

TEST(CMyString, EqualityOperatorSameStrings)
{
	CMyString str1("Test");
	CMyString str2("Test");
	EXPECT_TRUE(str1 == str2);
	EXPECT_FALSE(str1 != str2);
}

TEST(CMyString, EqualityOperatorDifferentStrings)
{
	CMyString str1("Hello");
	CMyString str2("World");
	EXPECT_FALSE(str1 == str2);
	EXPECT_TRUE(str1 != str2);
}

TEST(CMyString, EqualityOperatorEmptyStrings)
{
	CMyString str1;
	CMyString str2;
	EXPECT_TRUE(str1 == str2);
	EXPECT_FALSE(str1 != str2);
}

TEST(CMyString, EqualityOperatorDifferentLengthStrings)
{
	CMyString str1("Test");
	CMyString str2("Testing");
	EXPECT_FALSE(str1 == str2);
	EXPECT_TRUE(str1 != str2);
}

TEST(CMyString, EqualityOperatorSelfEquality)
{
	CMyString str("Test");
	EXPECT_TRUE(str == str);
	EXPECT_FALSE(str != str);
}

TEST(CMyString, ComparisonOperatorsAlphabeticalOrder)
{
	CMyString str1("apple");
	CMyString str2("banana");
	EXPECT_TRUE(str1 < str2);
	EXPECT_FALSE(str1 >= str2);
	EXPECT_FALSE(str1 > str2);
	EXPECT_TRUE(str1 <= str2);

	CMyString str3("hello");
	CMyString str4("world");
	EXPECT_TRUE(str4 > str3);
	EXPECT_TRUE(str4 >= str3);
	EXPECT_FALSE(str4 < str3);
	EXPECT_FALSE(str4 <= str3);

	CMyString str5("test");
	CMyString str6("test");
	EXPECT_FALSE(str5 > str6);
	EXPECT_TRUE(str5 >= str6);
	EXPECT_FALSE(str5 < str6);
	EXPECT_TRUE(str5 <= str6);
}

TEST(CMyString, ComparisonOperatorsEmptyStrings)
{
	CMyString str1;
	CMyString str2;
	EXPECT_FALSE(str1 > str2);
	EXPECT_TRUE(str1 >= str2);
	EXPECT_FALSE(str1 < str2);
	EXPECT_TRUE(str1 <= str2);
}

TEST(CMyString, ComparisonOperatorsSelfComparison)
{
	CMyString str("apple");
	EXPECT_FALSE(str > str);
	EXPECT_TRUE(str >= str);
	EXPECT_FALSE(str < str);
	EXPECT_TRUE(str <= str);
}

TEST(CMyString, OutputOperator)
{
	CMyString str("Test String");
	std::stringstream ss;
	ss << str;

	EXPECT_EQ(ss.str(), "Test String");
}

TEST(CMyString, InputOperator)
{
	CMyString str;
	std::stringstream ss("Hello World!");
	ss >> str;

	EXPECT_EQ(str.GetLength(), 5);
	EXPECT_STREQ(str.GetStringData(), "Hello");
}

TEST(CMyString, InputOutputOperatorChaining)
{
	CMyString str("Hello World!");
	std::stringstream ss;
	ss << str;
	ss >> str;

	EXPECT_EQ(str.GetLength(), 5);
	EXPECT_STREQ(str.GetStringData(), "Hello");
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
