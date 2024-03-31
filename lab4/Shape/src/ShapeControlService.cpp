#include "../include/ShapeControlService.h"
#include <algorithm>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>

std::shared_ptr<IShape> ConstructShape(const std::string& shapeName, const std::string& shapeInfo)
{
	if (shapeName == CLineSegment::NAME)
	{
		return std::make_shared<CLineSegment>(shapeInfo);
	}
	else if (shapeName == CCircle::NAME)
	{
		return std::make_shared<CCircle>(shapeInfo);
	}
	else if (shapeName == CTriangle::NAME)
	{
		return std::make_shared<CTriangle>(shapeInfo);
	}
	else if (shapeName == CRectangle::NAME)
	{
		return std::make_shared<CRectangle>(shapeInfo);
	}
	else
	{
		throw std::invalid_argument(std::format("Unknown shape name \"{}\"", shapeName));
	}
}

void ShapeControlService::ReadShapes(const std::string& inputFileName)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Error reading input file");
	}

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::istringstream iss(line);
		std::string shapeName;
		iss >> shapeName;

		try
		{
			m_shapes.emplace_back(ConstructShape(shapeName, line));
		}
		catch (const std::invalid_argument& e)
		{
			std::cout << e.what() << std::endl;
			continue;
		}
	}

	if (!inputFile.eof())
	{
		throw std::runtime_error("Error reading input file");
	}
}

void ShapeControlService::PrintShapeWithMaxAreaInfo() const
{
	auto maxPerimeterShape = *std::max_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b) { return a->GetArea() < b->GetArea(); });

	std::cout << "Shape with maximum area: " << maxPerimeterShape->ToString() << std::endl;
}

void ShapeControlService::PrintShapeWithMinPerimeterInfo() const
{
	auto minPerimeterShape = *std::min_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b) { return a->GetPerimeter() < b->GetPerimeter(); });

	std::cout << "Shape with minimum perimeter: " << minPerimeterShape->ToString() << std::endl;
}
