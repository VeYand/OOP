#include "../include/ShapeFactory.h"
#include "../include/CCircle.h"
#include "../include/CLineSegment.h"
#include "../include/CRectangle.h"
#include "../include/CTriangle.h"
#include <format>
#include <sstream>

namespace
{
std::shared_ptr<CLineSegment> constructCLineSegment(const std::string& info)
{
	std::istringstream iss(info);
	std::string shapeName;
	iss >> shapeName;

	double startPointX, startPointY, endPointX, endPointY;

	if (!(iss >> startPointX >> startPointY >> endPointX >> endPointY))
	{
		throw std::invalid_argument("Invalid line segment coordinates");
	}

	uint32_t outlineColor;

	if (!(iss >> std::hex >> outlineColor))
	{
		throw std::invalid_argument("Invalid color value");
	}

	return std::make_shared<CLineSegment>(
		CPoint(startPointX, startPointY),
		CPoint(endPointX, endPointY),
		outlineColor);
}

std::shared_ptr<CCircle> constructCCircle(const std::string& info)
{
	std::istringstream iss(info);
	std::string shapeName;
	iss >> shapeName;

	double centerX, centerY, radius;

	if (!(iss >> centerX >> centerY >> radius))
	{
		throw std::invalid_argument("Invalid circle parameters");
	}

	uint32_t outlineColor, fillColor;

	if (!(iss >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid color values");
	}

	return std::make_shared<CCircle>(
		CPoint(centerX, centerY),
		radius,
		outlineColor,
		fillColor);
}

std::shared_ptr<CTriangle> constructCTriangle(const std::string& info)
{
	std::istringstream iss(info);
	std::string shapeName;
	iss >> shapeName;

	double vertex1X, vertex1Y, vertex2X, vertex2Y, vertex3X, vertex3Y;

	if (!(iss >> vertex1X >> vertex1Y >> vertex2X >> vertex2Y >> vertex3X >> vertex3Y))
	{
		throw std::invalid_argument("Invalid triangle parameters");
	}

	uint32_t outlineColor, fillColor;

	if (!(iss >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid color values");
	}

	return std::make_shared<CTriangle>(
		CPoint(vertex1X, vertex1Y),
		CPoint(vertex2X, vertex2Y),
		CPoint(vertex3X, vertex3Y),
		outlineColor,
		fillColor);
}

std::shared_ptr<CRectangle> constructCRectangle(const std::string& info)
{
	std::istringstream iss(info);
	std::string shapeName;
	iss >> shapeName;

	double leftTopX, leftTopY, rightBottomX, rightBottomY;

	if (!(iss >> leftTopX >> leftTopY >> rightBottomX >> rightBottomY))
	{
		throw std::invalid_argument("Invalid rectangle parameters");
	}

	uint32_t outlineColor, fillColor;

	if (!(iss >> std::hex >> outlineColor >> fillColor))
	{
		throw std::invalid_argument("Invalid color values");
	}

	return std::make_shared<CRectangle>(
		CPoint(leftTopX, leftTopY),
		CPoint(rightBottomX, rightBottomY),
		outlineColor,
		fillColor);
}
} // namespace

std::shared_ptr<IShape> ShapeFactory::constructShape(const std::string& info)
{
	std::istringstream iss(info);
	std::string shapeName;
	iss >> shapeName;

	if (shapeName == CLineSegmentName)
	{
		return constructCLineSegment(info);
	}
	else if (shapeName == CCircleName)
	{
		return constructCCircle(info);
	}
	else if (shapeName == CTriangleName)
	{
		return constructCTriangle(info);
	}
	else if (shapeName == CRectangleName)
	{
		return constructCRectangle(info);
	}
	else
	{
		throw std::invalid_argument(std::format("Unknown shape name \"{}\"", shapeName));
	}
}
