#include "../include/CTriangle.h"
#include <cmath>
#include <format>
#include <sstream>
#include <stdexcept>

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
	double a, b, c;
	CalculateSideLengths(a, b, c);

	if ((a + b <= c) || (a + c <= b) || (b + c <= a)
		|| a < 0 || b < 0 || c < 0)
	{
		throw std::invalid_argument("Invalid triangle points");
	}
}

void CTriangle::CalculateSideLengths(double& a, double& b, double& c) const
{
	a = sqrt(pow(m_vertex2.x - m_vertex1.x, 2) + pow(m_vertex2.y - m_vertex1.y, 2));
	b = sqrt(pow(m_vertex3.x - m_vertex1.x, 2) + pow(m_vertex3.y - m_vertex1.y, 2));
	c = sqrt(pow(m_vertex3.x - m_vertex2.x, 2) + pow(m_vertex3.y - m_vertex2.y, 2));
}

double CTriangle::GetArea() const
{
	double a, b, c;
	CalculateSideLengths(a, b, c);

	double s = (a + b + c) / 2;

	return sqrt(s * (s - a) * (s - b) * (s - c));
}

double CTriangle::GetPerimeter() const
{
	double a, b, c;
	CalculateSideLengths(a, b, c);

	return a + b + c;
}

std::string CTriangle::ToString() const
{
	return std::format("CTriangle: Vertex1: ({}, {}) Vertex2: ({}, {}) Vertex3: ({}, {}) OutlineColor: {:08x} FillColor: {:08x} Area: {:.2f} Perimeter: {:.2f}",
		m_vertex1.x, m_vertex1.y, m_vertex2.x, m_vertex2.y, m_vertex3.x, m_vertex3.y, m_outlineColor, m_fillColor, GetArea(), GetPerimeter());
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}