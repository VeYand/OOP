#ifndef SHAPE_INCLUDE_CTRIANGLE_H
#define SHAPE_INCLUDE_CTRIANGLE_H

#include "CPoint.h"
#include "ICanvasDrawable.h"
#include "ISolidShape.h"

class CTriangle : public ISolidShape
{
public:
	CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] CPoint GetVertex1() const;
	[[nodiscard]] CPoint GetVertex2() const;
	[[nodiscard]] CPoint GetVertex3() const;
	void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
	void CalculateSideLengths(double& a, double& b, double& c) const;
	CPoint m_vertex1, m_vertex2, m_vertex3;
	uint32_t m_outlineColor, m_fillColor;
};

#endif // SHAPE_INCLUDE_CTRIANGLE_H
