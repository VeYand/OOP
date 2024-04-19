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
		|| rightBottom.y >= leftTop.y)
	{
		throw std::invalid_argument("Invalid rectangle points");
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
	return std::format("CRectangle: LeftTop: ({}, {}) RightBottom: ({}, {}) OutlineColor: {:08x} FillColor: {:08x} Area: {:.2f} Perimeter: {:.2f}",
		m_leftTop.x, m_leftTop.y, m_rightBottom.x, m_rightBottom.y, m_outlineColor, m_fillColor, GetArea(), GetPerimeter());
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
