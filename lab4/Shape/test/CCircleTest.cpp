#include "../include/CCircle.h"
#include <cmath>
#include <format>
#include <gtest/gtest.h>

TEST(CCircleTest, ConstructorFromParametersAndGetters)
{
	CPoint center = { 3, 4 };
	double radius = 3;
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0xFF0000;

	CCircle circle(center, radius, outlineColor, fillColor);

	EXPECT_EQ(circle.GetCenter().x, center.x);
	EXPECT_EQ(circle.GetCenter().y, center.y);
	EXPECT_EQ(circle.GetRadius(), radius);

	EXPECT_DOUBLE_EQ(circle.GetArea(), M_PI * radius * radius);
	EXPECT_DOUBLE_EQ(circle.GetPerimeter(), 2 * M_PI * radius);

	EXPECT_EQ(circle.GetOutlineColor(), outlineColor);
	EXPECT_EQ(circle.GetFillColor(), fillColor);
}

TEST(CCircleTest, ConstructorFromStringAndGetters)
{
	CCircle circle("circle 3 4 3 0xFF0000 0xFF0000");

	EXPECT_EQ(circle.GetCenter().x, 3);
	EXPECT_EQ(circle.GetCenter().y, 4);
	EXPECT_EQ(circle.GetRadius(), 3);

	EXPECT_DOUBLE_EQ(circle.GetArea(), M_PI * 3 * 3);
	EXPECT_DOUBLE_EQ(circle.GetPerimeter(), 2 * M_PI * 3);

	EXPECT_EQ(circle.GetOutlineColor(), 0xFF0000);
	EXPECT_EQ(circle.GetFillColor(), 0xFF0000);
}

TEST(CCircleTest, ConstructorFromInvalidStringInvalidParameterCount)
{
	EXPECT_THROW(CCircle("circle 3 4 3 0xFF0000"), std::invalid_argument);
}

TEST(CCircleTest, ConstructorFromInvalidStringInvalidName)
{
	EXPECT_THROW(CCircle("shape 3 4 3 0xFF0000 0xFF0000"), std::invalid_argument);
}

TEST(CCircleTest, ConstructorFromInvalidParameters)
{
	EXPECT_THROW(CCircle({ 3, 4 }, 0, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CCircle({ 3, 4 }, -1, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CCircle({ -1, 2 }, 2, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CCircle({ 2, -1 }, 2, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_NO_THROW(CCircle({ 0, 0 }, 2, 0xFF0000, 0xFF0000));
	EXPECT_NO_THROW(CCircle({ 1, 1 }, 1, 0xFF0000, 0xFF0000));
}

TEST(CCircleTest, ConstructorFromInvalidStringInvalidCoordinates)
{
	EXPECT_THROW(CCircle("circle 3 4 0 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CCircle("circle 3 4 -1 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CCircle("circle -1 2 2 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CCircle("circle 2 -1 2 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_NO_THROW(CCircle("circle 0 0 2 3 0xFF0000 0xFF0000"));
	EXPECT_NO_THROW(CCircle("circle 1 1 1 0xFF0000 0xFF0000"));
}

TEST(CCircleTest, ConstructorFromInvalidStringInvalidOutlineColor)
{
	EXPECT_THROW(CCircle("circle 1 1 1 invalid invalid"), std::invalid_argument);
}

TEST(CCircleTest, ToString)
{
	CPoint center = { 3, 4 };
	double radius = 3;
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0xFF0000;

	CCircle circle(center, radius, outlineColor, fillColor);

	std::string expectedString = std::format("{}: Center: ({}, {}) Radius: {} OutlineColor: {:08x} FillColor: {:08x}",
		CCircle::NAME, center.x, center.y, radius, outlineColor, fillColor);

	EXPECT_EQ(circle.ToString(), expectedString);
}