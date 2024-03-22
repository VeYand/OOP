#include "../include/BorTrieUtils.h"
#include <cstring>

const int ROOT = 0;
const char CHAR_ROOT = '~';

int GetAutoMove(int vertex, char symbol, std::vector<BohrVertex>& bohr)
{
	int nextVertex = bohr[vertex].nextVertex[static_cast<unsigned char>(symbol)];
	int suffixFromLastTransition = bohr[vertex].autoMove[static_cast<unsigned char>(symbol)];

	if (suffixFromLastTransition != NOT_USED)
	{
		return suffixFromLastTransition;
	}

	if (nextVertex != NOT_USED)
	{
		return nextVertex;
	}

	if (vertex == ROOT)
	{
		return ROOT;
	}

	return GetAutoMove(GetSuffixLink(vertex, bohr), symbol, bohr);
}

int GetSuffixLink(int vertex, std::vector<BohrVertex>& bohr)
{
	int suffixLink = bohr[vertex].suffixLink;
	int parent = bohr[vertex].parent;

	if (suffixLink != NOT_USED)
	{
		return suffixLink;
	}

	if (vertex == ROOT || parent == ROOT)
	{
		return ROOT;
	}

	return GetAutoMove(GetSuffixLink(parent, bohr), bohr[vertex].symbol, bohr);
}

int GetGoodSuffixLink(int vertex, std::vector<BohrVertex>& bohr)
{
	int suffixGoofLink = bohr[vertex].suffixGoodLink;

	if (suffixGoofLink != NOT_USED) {
		return suffixGoofLink;
	}

	int suffixLink = GetSuffixLink(vertex, bohr);

	if (suffixLink == ROOT)
	{
		return ROOT;
	}

	if (bohr[suffixLink].isTerminal) {
		return suffixLink;
	}

	return GetGoodSuffixLink(suffixLink, bohr);
}

void Check(int vertex, int startStr, std::vector<BohrVertex>& bohr, std::map<int, std::string>& substrings)
{
	for (int u = vertex; u != 0; u = GetGoodSuffixLink(u, bohr))
	{
		std::string& stringToReplace = *(bohr[u].ptr);
		if (bohr[u].isTerminal)
		{
			substrings[static_cast<int>(startStr - stringToReplace.length())] = stringToReplace;
		}
	}
}

BohrVertex MakeBohrVertex(int parent, char symbol)
{
	BohrVertex vertex{};
	memset(reinterpret_cast<void*>(vertex.nextVertex), 255, sizeof(vertex.nextVertex));
	memset(reinterpret_cast<void*>(vertex.autoMove), 255, sizeof(vertex.autoMove));
	vertex.isTerminal = false;
	vertex.suffixLink = NOT_USED;
	vertex.suffixGoodLink = NOT_USED;
	vertex.parent = parent;
	vertex.symbol = symbol;
	return vertex;
}

void AddStringToBohr(const std::string* ptr, std::vector<BohrVertex>& bohr)
{
	int num = 0;
	std::string str = *ptr;
	for (char ch : str)
	{
		if (int(bohr[num].nextVertex[static_cast<unsigned char>(ch)]) == NOT_USED)
		{
			bohr.push_back(MakeBohrVertex(num, ch));
			bohr[num].nextVertex[static_cast<unsigned char>(ch)] = int(bohr.size() - 1);
		}
		num = bohr[num].nextVertex[static_cast<unsigned char>(ch)];
	}
	bohr[num].isTerminal = true;
	bohr[num].ptr = const_cast<std::string*>(ptr);
}

std::vector<BohrVertex> CreateBohr(const Replacement& params)
{
	std::vector<BohrVertex> bohr;
	bohr.push_back(MakeBohrVertex(-1, CHAR_ROOT));
	for (const auto& item : params)
	{
		AddStringToBohr(&(item.first), bohr);
	}
	return bohr;
}