#ifndef SHAPE_INCLUDE_CCANVAS_H
#define SHAPE_INCLUDE_CCANVAS_H

#include "ICanvas.h"

class CCanvas : ICanvas
{
public:
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) override;
};

#endif // SHAPE_INCLUDE_CCANVAS_H
