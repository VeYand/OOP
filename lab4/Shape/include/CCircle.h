#ifndef SHAPE_INCLUDE_CCIRCLE_H
#define SHAPE_INCLUDE_CCIRCLE_H

#include "CPoint.h"
#include "ISolidShape.h"

class CCircle : public ISolidShape
{
public:
	constexpr static const std::string NAME = "circle";
	CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor);
	CCircle(const std::string& string);
	[[nodiscard]] double GetArea() const override;
	[[nodiscard]] double GetPerimeter() const override;
	[[nodiscard]] std::string ToString() const override;
	[[nodiscard]] uint32_t GetOutlineColor() const override;
	[[nodiscard]] uint32_t GetFillColor() const override;
	[[nodiscard]] CPoint GetCenter() const;
	[[nodiscard]] double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	uint32_t m_outlineColor, m_fillColor;
};

#endif // SHAPE_INCLUDE_CCIRCLE_H
