#include "../include/CRectangle.h"
#include <format>
#include <sstream>
#include <stdexcept>

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	if (rightBottom.x <= leftTop.x
		|| rightBottom.y >= leftTop.y
		|| rightBottom.x < 0
		|| rightBottom.y < 0
		|| leftTop.x < 0
		|| leftTop.y < 0)
	{
		throw std::invalid_argument("Invalid rectangle points");
	}
}

CRectangle::CRectangle(const std::string& string)
{
	std::istringstream iss(string);
	std::string shapeName;
	if (!(iss >> shapeName && shapeName == NAME))
	{
		throw std::invalid_argument("Invalid shape name");
	}

	if (!(iss >> m_leftTop.x >> m_leftTop.y >> m_rightBottom.x >> m_rightBottom.y))
	{
		throw std::invalid_argument("Invalid rectangle coordinates");
	}

	if (m_rightBottom.x <= m_leftTop.x
		|| m_rightBottom.y >= m_leftTop.y
		|| m_rightBottom.x < 0
		|| m_rightBottom.y < 0
		|| m_leftTop.x < 0
		|| m_leftTop.y < 0)
	{
		throw std::invalid_argument("Invalid rectangle points");
	}

	if (!(iss >> std::hex >> m_outlineColor >> m_fillColor))
	{
		throw std::invalid_argument("Invalid color values");
	}
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

std::string CRectangle::ToString() const
{
	return std::format("{}: LeftTop: ({}, {}) RightBottom: ({}, {}) OutlineColor: {:08x} FillColor: {:08x}", NAME, m_leftTop.x, m_leftTop.y, m_rightBottom.x, m_rightBottom.y, m_outlineColor, m_fillColor);
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

double CRectangle::GetWidth() const
{
	return m_rightBottom.x - m_leftTop.x;
}

double CRectangle::GetHeight() const
{
	return m_leftTop.y - m_rightBottom.y;
}
