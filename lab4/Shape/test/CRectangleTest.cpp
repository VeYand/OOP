#include "../include/CRectangle.h"
#include <gtest/gtest.h>

TEST(CRectangleTest, ConstructorFromParametersAndGetters)
{
	CPoint leftTop(0, 10);
	CPoint rightBottom(20, 0);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

	EXPECT_EQ(rectangle.GetLeftTop().x, leftTop.x);
	EXPECT_EQ(rectangle.GetLeftTop().y, leftTop.y);
	EXPECT_EQ(rectangle.GetRightBottom().x, rightBottom.x);
	EXPECT_EQ(rectangle.GetRightBottom().y, rightBottom.y);
	EXPECT_EQ(rectangle.GetOutlineColor(), outlineColor);
	EXPECT_EQ(rectangle.GetFillColor(), fillColor);
}

TEST(CRectangleTest, ConstructorFromInvalidParameters)
{
	EXPECT_THROW(CRectangle rectangle(CPoint(20, 10), CPoint(0, 0), 0xFF0000, 0x00FF00), std::invalid_argument);
}

TEST(CRectangleTest, GetArea)
{
	CPoint leftTop(0, 10);
	CPoint rightBottom(20, 0);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

	EXPECT_DOUBLE_EQ(rectangle.GetArea(), 200);
}

TEST(CRectangleTest, GetPerimeter)
{
	CPoint leftTop(0, 10);
	CPoint rightBottom(20, 0);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

	EXPECT_DOUBLE_EQ(rectangle.GetPerimeter(), 60);
}

TEST(CRectangleTest, ToString)
{
	CPoint leftTop(0, 10);
	CPoint rightBottom(20, 0);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

	std::string expectedString = "CRectangle: LeftTop: (0, 10) RightBottom: (20, 0) OutlineColor: 00ff0000 FillColor: 0000ff00 Area: 200.00 Perimeter: 60.00";

	EXPECT_EQ(rectangle.ToString(), expectedString);
}

TEST(CRectangleTest, DegenerateRectangle)
{
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	EXPECT_THROW(CRectangle(CPoint(0, 0), CPoint(0, 0), outlineColor, fillColor), std::invalid_argument);
	EXPECT_THROW(CRectangle(CPoint(0, 2), CPoint(0, 1), outlineColor, fillColor), std::invalid_argument);
	EXPECT_THROW(CRectangle(CPoint(0, 2), CPoint(-1, 2), outlineColor, fillColor), std::invalid_argument);
}
