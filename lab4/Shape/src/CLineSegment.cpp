#include "../include/CLineSegment.h"
#include <cmath>
#include <format>
#include <sstream>
#include <stdexcept>

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
	if (startPoint.x < 0
		|| startPoint.y < 0
		|| endPoint.x < 0
		|| endPoint.y < 0)
	{
		throw std::invalid_argument("Invalid line coordinates");
	}
}

CLineSegment::CLineSegment(const std::string& string)
{
	std::istringstream iss(string);
	std::string shapeName;
	if (!(iss >> shapeName && shapeName == NAME))
	{
		throw std::invalid_argument("Invalid shape name");
	}

	if (!(iss >> m_startPoint.x >> m_startPoint.y >> m_endPoint.x >> m_endPoint.y)
		|| m_startPoint.x < 0
		|| m_startPoint.y < 0
		|| m_endPoint.x < 0
		|| m_endPoint.y < 0)
	{
		throw std::invalid_argument("Invalid line segment coordinates");
	}

	if (!(iss >> std::hex >> m_outlineColor))
	{
		throw std::invalid_argument("Invalid color value");
	}
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return 0;
}

std::string CLineSegment::ToString() const
{
	return std::format("{}: StartPoint: ({}, {}) EndPoint: ({}, {}) OutlineColor: {:08x}", NAME, m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y, m_outlineColor);
}

uint32_t CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
