#ifndef SHAPE_INCLUDE_CCANVAS_H
#define SHAPE_INCLUDE_CCANVAS_H

#include "ICanvas.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <memory>

class CCanvas : public ICanvas
{
public:
	explicit CCanvas(std::shared_ptr<sf::RenderWindow> window);
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;

private:
	std::shared_ptr<sf::RenderWindow> m_window;
};

#endif // SHAPE_INCLUDE_CCANVAS_H
