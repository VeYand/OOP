#ifndef SHAPE_INCLUDE_CLINESEGMENT_H
#define SHAPE_INCLUDE_CLINESEGMENT_H

#include "CPoint.h"
#include "IShape.h"

class CLineSegment : public IShape
{
public:
	constexpr static const std::string NAME = "line_segment";
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor);
	CLineSegment(const std::string& string);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] CPoint GetStartPoint() const;
	[[nodiscard]] CPoint GetEndPoint() const;

private:
	CPoint m_startPoint, m_endPoint;
	uint32_t m_outlineColor;
};

#endif // SHAPE_INCLUDE_CLINESEGMENT_H