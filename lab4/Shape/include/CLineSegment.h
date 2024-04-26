#ifndef SHAPE_INCLUDE_CLINESEGMENT_H
#define SHAPE_INCLUDE_CLINESEGMENT_H

#include "CPoint.h"
#include "ICanvasDrawable.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;
	void Draw(std::shared_ptr<ICanvas> canvas) override;

private:
	CPoint m_startPoint, m_endPoint;
	uint32_t m_outlineColor;
};

#endif // SHAPE_INCLUDE_CLINESEGMENT_H
