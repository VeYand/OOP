#include "../include/MapUtilities.h"
#include <algorithm>

const int MAX_WIDTH = 100;
const int MAX_HEIGHT = 100;

const char EMPTY_CELL_SYMBOL = ' ';
const char POINT_SYMBOL = '0';
const char WALL_SYMBOL = '#';
const char FILL_SYMBOL = '-';

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
	while (std::getline(inputFile, line))
	{
		if (lineIndex >= MAX_HEIGHT)
		{
			break;
		}

		std::vector<SymbolCode> horizontalVector;
		for (int i = 0; i < line.length(); ++i)
		{
			if (i >= MAX_WIDTH)
			{
				break;
			}

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
			default:
				break;
			}
			outputFile << symbol;
		}
		outputFile << std::endl;
	}

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
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

bool InVector(const Position& pos, const std::vector<Position>& vec)
{
	return std::ranges::any_of(vec, [&](const Position& p) {
		return p.x == pos.x && p.y == pos.y;
	});
}

bool IsEdge(const Position& pos, const std::vector<std::vector<SymbolCode>>& map)
{
	if (pos.x < 0 || pos.y < 0 || pos.y >= map.size())
	{
		return true;
	}

	if (pos.x >= map[pos.y].size())
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

	while (!pointQueue.empty())
	{
		auto front = pointQueue.front();
		pointQueue.pop();

		if (InVector(front, visited))
		{
			continue;
		}

		visited.push_back(front);
		map[front.y][front.x] = SymbolCode::FILL;

		for (const auto& dir : fillDirections)
		{
			Position nextPos(front.x + dir.x, front.y + dir.y);
			if (!IsEdge(nextPos, map)
				&& map[nextPos.y][nextPos.x] != SymbolCode::WALL
				&& map[nextPos.y][nextPos.x] != SymbolCode::FILL
				&& !InVector(nextPos, visited))
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