#include "../include/Dictionary.h"
#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

using DictionaryType = std::map<std::string, std::vector<std::string>>;

const char WORD_SEPARATOR = ',';
const char TRANSLATE_SEPARATOR = ':';
const std::string WHITESPACE = " \n\r\t\f\v";
const std::string AGREE_COMMAND_SYMBOL = "y";
const std::string STOP_COMMAND_SYMBOL = "...";
const char ENTER_SYMBOL = '>';

std::string Ltrim(const std::string& str)
{
	size_t start = str.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : str.substr(start);
}

std::string Rtrim(const std::string& str)
{
	size_t end = str.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

std::string Trim(const std::string& str)
{
	return Rtrim(Ltrim(str));
}

std::string Lower(const std::string& str)
{
	auto newStr = str;
	std::transform(newStr.begin(), newStr.end(), newStr.begin(), ::tolower);
	return newStr;
}

bool IsTranslateExists(const DictionaryType& dict, const std::string& word)
{
	return dict.find(word) != dict.end();
}

void AddTranslate(DictionaryType& dict, const std::string& word, const std::string& translate)
{
	if (IsTranslateExists(dict, word))
	{
		dict[word].push_back(translate);
		return;
	}

	dict[word] = std::vector<std::string>{ translate };
}

void LoadDictionary(const std::string& filePath, DictionaryType& enToRuDict, DictionaryType& ruToEnDict)
{
	std::ifstream inputFile(filePath);

	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Cannot open input file");
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::string enWord;
		std::string ruWords;

		std::istringstream iss(line);
		std::getline(iss, enWord, TRANSLATE_SEPARATOR);
		std::getline(iss, ruWords);

		if (enWord.empty() || ruWords.empty())
		{
			continue;
		}

		enWord = Trim(enWord);

		std::istringstream ruWordsStream(ruWords);
		std::string ruWord;
		std::vector<std::string> ruWordsVector;

		while (std::getline(ruWordsStream, ruWord, WORD_SEPARATOR))
		{
			ruWord = Trim(ruWord);
			AddTranslate(enToRuDict, enWord, ruWord);
			AddTranslate(ruToEnDict, ruWord, enWord);
		}
	}

	if (!inputFile.eof())
	{
		throw std::runtime_error("Error in reading input file");
	}
}

void DumpDictionary(const std::string& filePath, const DictionaryType& dictionary)
{
	std::ofstream outputFile(filePath);

	if (!outputFile.is_open())
	{
		throw std::invalid_argument("Cannot open output file");
	}

	for (const auto& translate : dictionary)
	{
		outputFile << translate.first << TRANSLATE_SEPARATOR;
		for (size_t i = 0; i < translate.second.size(); ++i)
		{
			outputFile << translate.second[i];
			if (i < translate.second.size() - 1)
			{
				outputFile << WORD_SEPARATOR;
			}
		}
		outputFile << std::endl;
		if (!outputFile.flush())
		{
			throw std::runtime_error("Error in writing to output file");
		}
	}
}

std::string GetTranslate(DictionaryType& dict, const std::string& word)
{
	auto translates = dict[word];
	std::string translate;
	for (int i = 0; i < translates.size(); ++i)
	{
		translate += translates[i];
		if (i != translates.size() - 1)
		{
			translate += WORD_SEPARATOR;
		}
	}
	return translate;
}

bool IsForbiddenWord(const std::string& str)
{
	return std::any_of(
		str.begin(),
		str.end(),
		[&](char c) { return c == WORD_SEPARATOR || c == TRANSLATE_SEPARATOR; });
}

bool IsEnglishWord(const std::string& string)
{
	const std::string specialChars = "~`!@#$%^&*()_+={}[];-<>,.?/\\'\"|";

	auto isSpecialChar = [&](char c) {
		return std::any_of(
			specialChars.begin(),
			specialChars.end(),
			[&](char sc) { return sc == c; });
	};
	auto isValidChar = [&](char c) {
		return (c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9')
			|| isSpecialChar(c);
	};

	return std::all_of(string.begin(), string.end(), isValidChar);
}

void HandleUnknownWord(const std::string& word, DictionaryType& enToRuDict, DictionaryType& ruToEnDict, bool& isDictChanged)
{
	std::cout << std::format("Ќеизвестное слово У{}Ф. ¬ведите перевод или пустую строку дл€ отказа.", word) << std::endl;

	std::string translate;

	while (true)
	{
		std::cout << ENTER_SYMBOL;

		if (!std::getline(std::cin, translate) || translate.empty())
		{
			std::cout << std::format("—лово У{}Ф проигнорировано.", word) << std::endl;
			return;
		}

		if (!IsForbiddenWord(translate))
		{
			isDictChanged = true;
			if (IsEnglishWord(word))
			{
				AddTranslate(enToRuDict, word, translate);
				AddTranslate(ruToEnDict, translate, word);
			}
			else
			{
				AddTranslate(ruToEnDict, word, translate);
				AddTranslate(enToRuDict, translate, word);
			}

			std::cout << std::format("—лово У{}Ф сохранено в словаре как У{}Ф.", word, translate) << std::endl;
			return;
		}

		std::cout << std::format("Ќе используйте символы У{}Ф и У{}Ф", WORD_SEPARATOR, TRANSLATE_SEPARATOR) << std::endl;
	}
}

void HandleDictChange(const std::string& dictPath, const DictionaryType& enToRuDict)
{
	std::cout << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом." << std::endl;
	std::string command;
	if (std::getline(std::cin, command) && Lower(command) == AGREE_COMMAND_SYMBOL)
	{
		std::cout << "»зменени€ сохранены." << std::endl;
		DumpDictionary(dictPath, enToRuDict);
	}
	else
	{
		std::cout << "»зменени€ не будут сохранены." << std::endl;
	}
}

void RunDictionary(const std::string& dictPath)
{
	DictionaryType enToRuDict;
	DictionaryType ruToEnDict;

	try
	{
		LoadDictionary(dictPath, enToRuDict, ruToEnDict);
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << "Ќе удалось открыть файл, будет создан новый словарь" << std::endl;
	}

	bool isDictChanged = false;
	while (true)
	{
		std::cout << ENTER_SYMBOL;
		std::string word;

		if (!std::getline(std::cin, word) || word == STOP_COMMAND_SYMBOL)
		{
			break;
		}

		if (word.empty())
		{
			continue;
		}

		if (IsForbiddenWord(word))
		{
			std::cout << std::format("Ќе используйте символы У{}Ф и У{}Ф", WORD_SEPARATOR, TRANSLATE_SEPARATOR) << std::endl;
		}

		auto isEnglishWord = IsEnglishWord(word);
		if (isEnglishWord && IsTranslateExists(enToRuDict, word))
		{
			std::cout << GetTranslate(enToRuDict, word) << std::endl;
		}
		else if (!isEnglishWord && IsTranslateExists(ruToEnDict, word))
		{
			std::cout << GetTranslate(ruToEnDict, word) << std::endl;
		}
		else
		{
			HandleUnknownWord(word, enToRuDict, ruToEnDict, isDictChanged);
		}
	}

	if (isDictChanged)
	{
		HandleDictChange(dictPath, enToRuDict);
	}

	std::cout << "ƒо свидани€." << std::endl;
}
