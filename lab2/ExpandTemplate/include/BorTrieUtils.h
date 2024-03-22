#include "ExpandTemplate.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifndef BORTRIEUTILS_SRC_BORTRIEUTILS_H
#define BORTRIEUTILS_SRC_BORTRIEUTILS_H

const int NOT_USED = -1;

struct BohrVertex
{
	int nextVertex[255]{NOT_USED};
	std::string *ptr; // указатель на строку в params
	int parent; // родитель
	int autoMove[255]{NOT_USED}; // показывает ссылку на сына от последнего перехода
	int suffixLink;// суффиксальная ссылка
	int suffixGoodLink; // "хорошая" суффиксальная ссылка
	char symbol; // символ на ребре от родителя
	bool isTerminal;
};

std::vector<BohrVertex> CreateBohr(const std::map <std::string, std::string>& params);

int GetSuffixLink(int vertex, std::vector<BohrVertex>& bohr);

int GetAutoMove(int vertex, char symbol, std::vector<BohrVertex>& bohr);

void Check(int vertex, int startStr, std::vector<BohrVertex>& bohr, std::map<int, std::string>& substrings);

#endif // BORTRIEUTILS_SRC_BORTRIEUTILS_H
