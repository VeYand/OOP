#include "../src/Dictionary.cpp"
#include <fstream>
#include <gtest/gtest.h>
#include <windows.h>

TEST(dictionary, translate_exists)
{
	DictionaryType dict;
	dict["cat"] = { "�����" };

	EXPECT_TRUE(IsTranslateExists(dict, "cat"));
	EXPECT_FALSE(IsTranslateExists(dict, "dog"));
}

TEST(dictionary, add_translate)
{
	DictionaryType dict;
	AddTranslate(dict, "cat", "�����");

	EXPECT_TRUE(IsTranslateExists(dict, "cat"));
	EXPECT_EQ(dict["cat"].size(), 1);
	EXPECT_EQ(dict["cat"][0], "�����");

	AddTranslate(dict, "cat", "���");
	EXPECT_EQ(dict["cat"].size(), 2);
	EXPECT_EQ(dict["cat"][1], "���");
}

TEST(dictionary, load_dict)
{
	DictionaryType enToRuDict, ruToEnDict;

	EXPECT_NO_THROW(LoadDictionary("../test/data/input.txt", enToRuDict, ruToEnDict));
	EXPECT_TRUE(IsTranslateExists(enToRuDict, "cat"));
	EXPECT_EQ(enToRuDict["cat"].size(), 2);
	EXPECT_EQ(enToRuDict["cat"][0], "���");
	EXPECT_EQ(enToRuDict["cat"][1], "�����");

	EXPECT_TRUE(IsTranslateExists(ruToEnDict, "���"));
	EXPECT_EQ(ruToEnDict["���"].size(), 2);
	EXPECT_EQ(ruToEnDict["���"][0], "home");
	EXPECT_EQ(ruToEnDict["���"][1], "house");
}

TEST(dictionary, load_nonexistent_dict)
{
	DictionaryType enToRuDict, ruToEnDict;

	EXPECT_THROW(LoadDictionary("data/test.txt", enToRuDict, ruToEnDict), std::invalid_argument);
}

TEST(dictionary, get_translate)
{
	DictionaryType dict;
	AddTranslate(dict, "cat", "�����");
	AddTranslate(dict, "cat", "���");

	EXPECT_EQ("�����,���", GetTranslate(dict, "cat"));
}

TEST(dictionary, dump_dictionary)
{
	DictionaryType dict;
	dict["cat"] = { "�����" };
	dict["dog"] = { "������", "���" };

	const std::string tempFilePath = "temp_dict.txt";
	EXPECT_NO_THROW(DumpDictionary(tempFilePath, dict));

	std::ifstream outputFile(tempFilePath);
	EXPECT_TRUE(outputFile.is_open());

	std::string line;
	std::getline(outputFile, line);
	EXPECT_EQ(line, "cat:�����");

	std::getline(outputFile, line);
	EXPECT_EQ(line, "dog:������,���");

	outputFile.close();
	std::remove(tempFilePath.c_str());
}

TEST(dictionary, get_translate_nonexistent_word)
{
	DictionaryType dict;

	EXPECT_EQ(GetTranslate(dict, "apple"), "");
}

TEST(dictionary, handle_unknown_word)
{
	DictionaryType enToRuDict, ruToEnDict;

	const std::string unknownWord = "apple";
	const std::string translation = "������";

	std::istringstream iss(translation);
	std::streambuf* cinBackup = std::cin.rdbuf(iss.rdbuf());

	bool isDictChanged;
	HandleUnknownWord(unknownWord, enToRuDict, ruToEnDict, isDictChanged);

	std::cin.rdbuf(cinBackup);

	EXPECT_TRUE(IsTranslateExists(enToRuDict, unknownWord));
	EXPECT_EQ(GetTranslate(enToRuDict, unknownWord), translation);
}

GTEST_API_ int main(int argc, char** argv)
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}