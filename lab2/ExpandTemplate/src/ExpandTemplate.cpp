#include "../include/ExpandTemplate.h"
#include "../include/BorTrieUtils.h"
#include <vector>

std::map<int, std::string> SearchSubstrings(const std::string& basicString, std::vector<BohrVertex>& bohr)
{
	std::map<int, std::string> substrings;
	int currentVertex = 0;
	for (int i = 0; i < basicString.length(); i++)
	{
		currentVertex = GetAutoMove(currentVertex, basicString[i], bohr);
		Check(currentVertex, i + 1, bohr, substrings);
	}
	return substrings;
}

std::string ExpandTemplate(const std::string& basicString, const Replacement& params)
{
	auto bohr = CreateBohr(params);
	auto substrings = SearchSubstrings(basicString, bohr);
	std::string resultStr;
	size_t pos = 0;
	for (auto& substring : substrings)
	{
		int substringStartPos = substring.first;
		auto stringToReplace = substring.second;
		if (substringStartPos >= pos)
		{
			resultStr += basicString.substr(pos, substringStartPos - pos);
			pos = substringStartPos;
			resultStr += params.find(stringToReplace)->second;
			pos += stringToReplace.length();
		}
	}
	resultStr += basicString.substr(pos, basicString.length() - pos);
	return resultStr;
}