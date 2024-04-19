#include "../include/CCircle.h"
#include <cmath>
#include <format>
#include <stdexcept>

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (radius <= 0)
	{
		throw std::invalid_argument("Invalid radius");
	}
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	return std::format("CCircle: Center: ({}, {}) Radius: {} OutlineColor: {:08x} FillColor: {:08x} Area: {:.2f} Perimeter: {:.2f}",
		m_center.x, m_center.y, m_radius, m_outlineColor, m_fillColor, GetArea(), GetPerimeter());
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}
