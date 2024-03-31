#include "../include/CCircle.h"
#include <cmath>
#include <format>
#include <sstream>
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

	if (center.x < 0 || center.y < 0)
	{
		throw std::invalid_argument("Invalid center coordinates");
	}
}

CCircle::CCircle(const std::string& string)
{
	std::istringstream iss(string);
	std::string shapeName;
	if (!(iss >> shapeName && shapeName == NAME))
	{
		throw std::invalid_argument("Invalid shape name");
	}

	if (!(iss >> m_center.x >> m_center.y >> m_radius))
	{
		throw std::invalid_argument("Invalid circle parameters");
	}

	if (m_radius <= 0)
	{
		throw std::invalid_argument("Invalid radius");
	}

	if (m_center.x < 0 || m_center.y < 0)
	{
		throw std::invalid_argument("Invalid center coordinates");
	}

	if (!(iss >> std::hex >> m_outlineColor >> m_fillColor))
	{
		throw std::invalid_argument("Invalid color values");
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
	return std::format("{}: Center: ({}, {}) Radius: {} OutlineColor: {:08x} FillColor: {:08x}", NAME, m_center.x, m_center.y, m_radius, m_outlineColor, m_fillColor);
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
