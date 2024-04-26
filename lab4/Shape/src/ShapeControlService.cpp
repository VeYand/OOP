#include "../include/ShapeControlService.h"
#include "../include/ShapeFactory.h"
#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>

namespace
{
const std::string EXIT_COMMAND = "...";
}

void ShapeControlService::ReadShapes(std::istream& input)
{
	std::string line;
	while (std::getline(input, line))
	{
		if (line == EXIT_COMMAND)
		{
			break;
		}

		try
		{
			m_shapes.emplace_back(ShapeFactory::constructShape(line));
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}
}

void ShapeControlService::ReadShapes(const std::string& inputFileName)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Error reading input file");
	}

	ReadShapes(inputFile);

	if (!inputFile.bad())
	{
		throw std::runtime_error("Error reading input file");
	}
}

void ShapeControlService::PrintShapeWithMaxAreaInfo() const
{
	if (m_shapes.empty())
	{
		std::cout << "Empty shape list" << std::endl;
		return;
	}

	auto maxAreaShape = std::max_element(
		m_shapes.begin(),
		m_shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetArea() < b->GetArea();
		});

	std::cout << "Shape with maximum area: "
			  << (*maxAreaShape)->ToString() << std::endl;
}

void ShapeControlService::PrintShapeWithMinPerimeterInfo() const
{
	if (m_shapes.empty())
	{
		std::cout << "Empty shape list" << std::endl;
		return;
	}

	auto minPerimeterShape = std::min_element(
		m_shapes.begin(),
		m_shapes.end(),
		[](const auto& a, const auto& b) {
			return a->GetPerimeter() < b->GetPerimeter();
		});

	std::cout << "Shape with minimum perimeter: "
			  << (*minPerimeterShape)->ToString() << std::endl;
}

std::vector<std::shared_ptr<IShape>> ShapeControlService::GetShapes() const
{
	return m_shapes;
}
