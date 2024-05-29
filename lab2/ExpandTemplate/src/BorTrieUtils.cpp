#include "../include/BorTrieUtils.h"

BohrTrie::BohrTrie() {
	m_bohr.emplace_back();
}

int BohrTrie::GetAutoMove(int vertex, char symbol) {
	int nextVertex = m_bohr[vertex].nextVertex[static_cast<unsigned char>(symbol)];
	int suffixFromLastTransition = m_bohr[vertex].autoMove;

	if (suffixFromLastTransition != NOT_USED)
		return suffixFromLastTransition;

	if (nextVertex != NOT_USED)
		return nextVertex;

	if (vertex == 0)
		return 0;

	return GetAutoMove(GetSuffixLink(vertex), symbol);
}

int BohrTrie::GetSuffixLink(int vertex) {
	int& suffixLink = m_bohr[vertex].suffixLink;
	int parent = m_bohr[vertex].parent;

	if (suffixLink != NOT_USED)
		return suffixLink;

	if (vertex == 0 || parent == 0)
		return 0;

	return suffixLink = GetAutoMove(GetSuffixLink(parent), m_bohr[vertex].symbol);
}

int BohrTrie::GetGoodSuffixLink(int vertex) {
	int& suffixGoodLink = m_bohr[vertex].suffixGoodLink;

	if (suffixGoodLink != NOT_USED)
		return suffixGoodLink;

	int suffixLink = GetSuffixLink(vertex);

	if (suffixLink == 0)
		return 0;

	if (m_bohr[suffixLink].isTerminal)
		return suffixGoodLink = suffixLink;

	return suffixGoodLink = GetGoodSuffixLink(suffixLink);
}

void BohrTrie::Check(int vertex, int startStr, std::map<int, std::string>& substrings) {
	for (int u = vertex; u != 0; u = GetGoodSuffixLink(u)) {
		std::string& stringToReplace = *(m_bohr[u].ptr);
		if (m_bohr[u].isTerminal)
			substrings[static_cast<int>(startStr - stringToReplace.length())] = stringToReplace;
	}
}

void BohrTrie::AddString(const std::string& str) {
	int num = 0;
	for (char ch : str) {
		if (m_bohr[num].nextVertex[ch] == NOT_USED) {
			m_bohr.emplace_back(num, ch);
			m_bohr[num].nextVertex[ch] = static_cast<int>(m_bohr.size()) - 1;
		}
		num = m_bohr[num].nextVertex[ch];
	}
	m_bohr[num].isTerminal = true;
	m_bohr[num].ptr = const_cast<std::string*>(&str);
}

void BohrTrie::Build(const std::vector<std::string>& strings) {
	for (const auto& str : strings)
		AddString(str);
}
