#include "../include/CCanvas.h"
#include "SFML/Graphics.hpp"
#include <utility>

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(from.x, from.y);
	line[1].position = sf::Vector2f(to.x, to.y);
	line[0].color = sf::Color(lineColor);
	line[1].color = sf::Color(lineColor);

	m_window->draw(line);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor)
{
	if (points.empty())
		return;

	sf::VertexArray polygon(sf::PrimitiveType::Quads, points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon[i].position = sf::Vector2f(points[i].x, points[i].y);
		polygon[i].color = sf::Color(fillColor);
	}

	m_window->draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x, center.y);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color(lineColor));
	circle.setOutlineThickness(2);

	m_window->draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle(radius);
	circle.setPosition(center.x, center.y);
	circle.setFillColor(sf::Color(fillColor));
	circle.setOutlineColor(sf::Color::Transparent);

	m_window->draw(circle);
}

CCanvas::CCanvas(std::shared_ptr<sf::RenderWindow> window)
{
	m_window = std::move(window);
}
