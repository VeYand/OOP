#include "../include/CLineSegment.h"
#include <gtest/gtest.h>

TEST(CLineSegmentTest, ConstructorFromParametersAndGetters)
{
	CPoint startPoint(0, 0);
	CPoint endPoint(3, 4);
	uint32_t outlineColor = 0xFF0000;

	CLineSegment line(startPoint, endPoint, outlineColor);

	EXPECT_EQ(line.GetStartPoint().x, startPoint.x);
	EXPECT_EQ(line.GetStartPoint().y, startPoint.y);
	EXPECT_EQ(line.GetEndPoint().x, endPoint.x);
	EXPECT_EQ(line.GetEndPoint().y, endPoint.y);
	EXPECT_EQ(line.GetOutlineColor(), outlineColor);
}

TEST(CLineSegmentTest, GetPerimeter)
{
	CPoint startPoint(0, 0);
	CPoint endPoint(3, 4);
	uint32_t outlineColor = 0xFF0000;

	CLineSegment line(startPoint, endPoint, outlineColor);

	EXPECT_DOUBLE_EQ(line.GetPerimeter(), 5);
}

TEST(CLineSegmentTest, ToString)
{
	CPoint startPoint(0, 0);
	CPoint endPoint(3, 4);
	uint32_t outlineColor = 0xFF0000;

	CLineSegment line(startPoint, endPoint, outlineColor);

	std::string expectedString = "CLineSegment: StartPoint: (0, 0) EndPoint: (3, 4) OutlineColor: 00ff0000 Area: 0.00 Perimeter: 5.00";

	EXPECT_EQ(line.ToString(), expectedString);
}

TEST(CRectangleTest, DegenerateLineSegment)
{
	uint32_t outlineColor = 0xFF0000;

	EXPECT_THROW(CLineSegment(CPoint(0, 0), CPoint(0, 0), outlineColor), std::invalid_argument);
}
