#ifndef SHAPE_INCLUDE_ICANVAS_H
#define SHAPE_INCLUDE_ICANVAS_H

#include "CPoint.h"
#include <cstdint>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(CPoint from, CPoint to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint center, double radius, uint32_t fillColor) = 0;
};

#endif // SHAPE_INCLUDE_ICANVAS_H
