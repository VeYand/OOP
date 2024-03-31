#include "../include/CLineSegment.h"
#include <format>
#include <gtest/gtest.h>

TEST(CLineSegmentTest, ConstructorFromParametersAndGetters)
{
	CPoint startPoint = { 0, 0 };
	CPoint endPoint = { 3, 4 };
	uint32_t outlineColor = 0xFF0000;

	CLineSegment line(startPoint, endPoint, outlineColor);

	EXPECT_EQ(line.GetStartPoint().x, startPoint.x);
	EXPECT_EQ(line.GetStartPoint().y, startPoint.y);
	EXPECT_EQ(line.GetEndPoint().x, endPoint.x);
	EXPECT_EQ(line.GetEndPoint().y, endPoint.y);

	EXPECT_EQ(line.GetOutlineColor(), outlineColor);
}

TEST(CLineSegmentTest, ConstructorFromStringAndGetters)
{
	CLineSegment line("line_segment 0 0 3 4 0xFF0000");

	EXPECT_EQ(line.GetStartPoint().x, 0);
	EXPECT_EQ(line.GetStartPoint().y, 0);
	EXPECT_EQ(line.GetEndPoint().x, 3);
	EXPECT_EQ(line.GetEndPoint().y, 4);

	uint32_t outlineColor = 0xFF0000;
	EXPECT_EQ(line.GetOutlineColor(), outlineColor);
}

TEST(CLineSegmentTest, ConstructorFromInvalidStringInvalidParameterCount)
{
	EXPECT_THROW(CLineSegment("line_segment 0 0 3 4"), std::invalid_argument);
}

TEST(CLineSegmentTest, ConstructorFromInvalidStringInvalidName)
{
	EXPECT_THROW(CLineSegment("LineSegment 0 0 3 4 0xFF0000"), std::invalid_argument);
}

TEST(CLineSegmentTest, ConstructorFromInvalidStringInvalidCoordinates)
{
	EXPECT_THROW(CLineSegment("line_segment b a 3 4 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CLineSegment("line_segment 0 -1 3 4 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CLineSegment("line_segment -1 0 3 4 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CLineSegment("line_segment 0 0 -3 4 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CLineSegment("line_segment 1 1 3 -4 0xFF0000"), std::invalid_argument);
}

TEST(CLineSegmentTest, ConstructorFromInvalidParametersInvalidCoordinates)
{
	EXPECT_THROW(CLineSegment({ 0, -1 }, { 3, 4 }, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CLineSegment({ -1, 0 }, { 3, 4 }, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CLineSegment({ 0, 0 }, { -3, 4 }, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CLineSegment({ 0, 0 }, { 3, -4 }, 0xFF0000), std::invalid_argument);
}

TEST(CLineSegmentTest, ConstructorFromInvalidStringInvalidOutlineColor)
{
	EXPECT_THROW(CLineSegment("line_segment 0 0 3 4 invalid"), std::invalid_argument);
}

TEST(CLineSegmentTest, AreaAndPerimeter)
{
	CPoint startPoint = { 0, 0 };
	CPoint endPoint = { 3, 4 };
	uint32_t outlineColor = 0xFF0000;

	CLineSegment line(startPoint, endPoint, outlineColor);

	EXPECT_DOUBLE_EQ(line.GetArea(), 0.0);

	EXPECT_DOUBLE_EQ(line.GetPerimeter(), 0.0);
}

TEST(CLineSegmentTest, ToString)
{
	CPoint startPoint = { 0, 0 };
	CPoint endPoint = { 3, 4 };
	uint32_t outlineColor = 0xFF0000;

	CLineSegment line(startPoint, endPoint, outlineColor);
	std::string expectedString = std::format("{}: StartPoint: ({}, {}) EndPoint: ({}, {}) OutlineColor: {:08x}",
		CLineSegment::NAME, startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);

	EXPECT_EQ(line.ToString(), expectedString);
}