#include <format>
#include <fstream>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#ifndef FILL_INCLUDE_MAPUTILITIES_H
#define FILL_INCLUDE_MAPUTILITIES_H

struct Position
{
public:
	int x;
	int y;

	Position(int x, int y)
		: x(x)
		, y(y)
	{
	}
};

enum class SymbolCode {
	EMPTY_CELL = 0,
	POINT = 1,
	WALL = 2,
	FILL = 3
};

std::vector<std::vector<SymbolCode>> ReadMap(const std::string& inputFilePath);
std::vector<Position> GetPointPositions(const std::vector<std::vector<SymbolCode>>& map);
void FillArea(std::vector<std::vector<SymbolCode>>& map, const Position& point);
void WriteMap(const std::string& outputFilePath, const std::vector<std::vector<SymbolCode>>& map);
void FillMap(const std::string& inputFileName, const std::string& outputFileName);

#endif // FILL_INCLUDE_MAPUTILITIES_H
