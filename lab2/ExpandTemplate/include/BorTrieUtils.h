#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifndef BORTRIEUTILS_SRC_BORTRIEUTILS_H
#define BORTRIEUTILS_SRC_BORTRIEUTILS_H

const int NOT_USED = -1;
const int ALPHABET_SIZE = 256;

struct BohrVertex {
	std::vector<int> nextVertex;
	std::string* ptr;
	int parent;
	int autoMove;
	int suffixLink;
	int suffixGoodLink;
	char symbol;
	bool isTerminal;

	explicit BohrVertex(int parent = -1, char symbol = '\0')
		: nextVertex(ALPHABET_SIZE, NOT_USED), ptr(nullptr),
		parent(parent), autoMove(NOT_USED),
		suffixLink(NOT_USED), suffixGoodLink(NOT_USED),
		symbol(symbol), isTerminal(false) {}
};

class BohrTrie {
private:
	std::vector<BohrVertex> m_bohr;
public:
	BohrTrie();
	void AddString(const std::string& str);
	void Build(const std::vector<std::string>& strings);
	int GetAutoMove(int vertex, char symbol);
	int GetSuffixLink(int vertex);
	int GetGoodSuffixLink(int vertex);
	void Check(int vertex, int startStr, std::map<int, std::string>& substrings);
};
#endif // BORTRIEUTILS_SRC_BORTRIEUTILS_H
