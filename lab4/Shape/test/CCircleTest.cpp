#include "../include/CCircle.h"
#include <cmath>
#include <format>
#include <gtest/gtest.h>

TEST(CCircleTest, ConstructorFromParametersAndGetters)
{
	CPoint center(0, 0);
	double radius = 5.0;
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CCircle circle(center, radius, outlineColor, fillColor);

	EXPECT_EQ(circle.GetCenter().x, center.x);
	EXPECT_EQ(circle.GetCenter().y, center.y);
	EXPECT_EQ(circle.GetRadius(), radius);
	EXPECT_EQ(circle.GetOutlineColor(), outlineColor);
	EXPECT_EQ(circle.GetFillColor(), fillColor);
}

TEST(CCircleTest, ConstructorFromInvalidParameters)
{
	EXPECT_THROW(CCircle circle(CPoint(0, 0), -5.0, 0xFF0000, 0x00FF00), std::invalid_argument);
}

TEST(CCircleTest, ToString)
{
	CPoint center(0, 0);
	double radius = 5.0;
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CCircle circle(center, radius, outlineColor, fillColor);

	std::string expectedString = "CCircle: Center: (0, 0) Radius: 5 OutlineColor: 00ff0000 FillColor: 0000ff00 Area: 78.54 Perimeter: 31.42";

	EXPECT_EQ(circle.ToString(), expectedString);
}

TEST(CCircleTest, GetArea)
{
	CPoint center(0, 0);
	double radius = 5.0;
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CCircle circle(center, radius, outlineColor, fillColor);

	double expectedArea = 78.54;

	EXPECT_NEAR(circle.GetArea(), expectedArea, 0.01);
}

TEST(CCircleTest, GetPerimeter)
{
	CPoint center(0, 0);
	double radius = 5.0;
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CCircle circle(center, radius, outlineColor, fillColor);

	double expectedPerimeter = 31.42;

	EXPECT_NEAR(circle.GetPerimeter(), expectedPerimeter, 0.01);
}

TEST(CRectangleTest, DegenerateCircle)
{
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	EXPECT_THROW(CCircle(CPoint(0, 0), 0, outlineColor, fillColor), std::invalid_argument);
	EXPECT_THROW(CCircle(CPoint(0, 0), -1, outlineColor, fillColor), std::invalid_argument);
}