#include "../include/MapUtilities.h"
#include <algorithm>

const int MAX_WIDTH = 100;
const int MAX_HEIGHT = 100;

const char EMPTY_CELL_SYMBOL = ' ';
const char POINT_SYMBOL = '0';
const char WALL_SYMBOL = '#';
const char FILL_SYMBOL = '-';

struct Position
{
public:
	int x;
	int y;
};

enum class SymbolCode
{
	EMPTY_CELL = 0,
	POINT = 1,
	WALL = 2,
	FILL = 3
};

std::vector<std::vector<SymbolCode>> ReadMap(const std::string& inputFilePath)
{
	std::ifstream inputFile(inputFilePath);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFilePath + " for reading");
	}

	std::vector<std::vector<SymbolCode>> map;
	std::string line;
	int lineIndex = 0;
	while (std::getline(inputFile, line) && lineIndex < MAX_HEIGHT)
	{
		std::vector<SymbolCode> horizontalVector;

		for (int i = 0; i < line.length() && i < MAX_WIDTH; ++i)
		{
			SymbolCode symbolCode = SymbolCode::EMPTY_CELL;
			if (line[i] == POINT_SYMBOL)
			{
				symbolCode = SymbolCode::POINT;
			}
			else if (line[i] == WALL_SYMBOL)
			{
				symbolCode = SymbolCode::WALL;
			}

			horizontalVector.push_back(symbolCode);
		}
		map.push_back(horizontalVector);

		++lineIndex;
	}

	if (inputFile.bad())
	{
		throw std::runtime_error("Error reading input file");
	}

	return map;
}

void WriteMap(const std::string& outputFilePath, const std::vector<std::vector<SymbolCode>>& map)
{
	std::ofstream outputFile(outputFilePath);

	if (!outputFile.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFilePath + " for writing");
	}

	for (const auto& horizontalVector : map)
	{
		for (const auto& symbolCode : horizontalVector)
		{
			char symbol = EMPTY_CELL_SYMBOL;
			switch (symbolCode)
			{
			case SymbolCode::WALL:
				symbol = WALL_SYMBOL;
				break;
			case SymbolCode::FILL:
				symbol = FILL_SYMBOL;
				break;
			case SymbolCode::POINT:
				symbol = POINT_SYMBOL;
				break;
			default:
				break;
			}
			outputFile << symbol;
		}
		outputFile << std::endl;

		if (!outputFile.flush())
		{
			throw std::runtime_error("Failed to save data on disk");
		}
	}
}

std::vector<Position> GetPointPositions(const std::vector<std::vector<SymbolCode>>& map)
{
	std::vector<Position> positions;

	for (auto row = 0; row < map.size(); ++row)
	{
		for (auto column = 0; column < map[row].size(); ++column)
		{
			if (map[row][column] == SymbolCode::POINT)
			{
				positions.emplace_back(column, row);
			}
		}
	}

	return positions;
}

bool IsEdge(const Position& pos, const std::vector<std::vector<SymbolCode>>& map)
{
	if (pos.x < 0 || pos.y < 0 || pos.y >= map.size() || pos.x >= map[pos.y].size())
	{
		return true;
	}

	return false;
}

void FillArea(std::vector<std::vector<SymbolCode>>& map, const Position& point)
{
	if (IsEdge(point, map))
	{
		return;
	}

	if (map[point.y][point.x] != SymbolCode::POINT)
	{
		return;
	}

	const std::vector<Position> fillDirections = {
		{ 1, 0 },
		{ -1, 0 },
		{ 0, 1 },
		{ 0, -1 }
	};

	std::vector<Position> visited;
	std::queue<Position> pointQueue;
	pointQueue.push(point);
	bool isStartPosition = true;

	while (!pointQueue.empty())
	{
		auto front = pointQueue.front();
		pointQueue.pop();

		if (!isStartPosition && map[front.y][front.x] != SymbolCode::EMPTY_CELL)
		{
			continue;
		}

		visited.push_back(front);
		map[front.y][front.x] = isStartPosition ? SymbolCode::POINT : SymbolCode::FILL;
		isStartPosition = false;

		for (const auto& dir : fillDirections)
		{
			Position nextPos(front.x + dir.x, front.y + dir.y);
			if (!IsEdge(nextPos, map)
				&& map[nextPos.y][nextPos.x] == SymbolCode::EMPTY_CELL)
			{
				pointQueue.push(nextPos);
			}
		}
	}
}

void FillMap(const std::string& inputFileName, const std::string& outputFileName)
{
	auto map = ReadMap(inputFileName);
	auto points = GetPointPositions(map);

	for (const auto& point : points)
	{
		FillArea(map, point);
	}

	WriteMap(outputFileName, map);
}