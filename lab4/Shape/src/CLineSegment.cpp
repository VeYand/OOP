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
	if (startPoint.x == endPoint.x
		&& startPoint.y == endPoint.y)
	{
		throw std::invalid_argument("Invalid line coordinates");
	}
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return sqrt(pow(m_endPoint.x - m_startPoint.x, 2) + pow(m_endPoint.y - m_startPoint.y, 2));
}

std::string CLineSegment::ToString() const
{
	return std::format("CLineSegment: StartPoint: ({}, {}) EndPoint: ({}, {}) OutlineColor: {:08x} Area: {:.2f} Perimeter: {:.2f}",
		m_startPoint.x, m_startPoint.y, m_endPoint.x, m_endPoint.y, m_outlineColor, GetArea(), GetPerimeter());
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
