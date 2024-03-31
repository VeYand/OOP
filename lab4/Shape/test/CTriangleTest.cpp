#include "../include/CTriangle.h"
#include <cmath>
#include <format>
#include <gtest/gtest.h>

TEST(CTriangleTest, ConstructorFromParametersAndGetters)
{
	CPoint vertex1 = { 0, 0 };
	CPoint vertex2 = { 0, 3 };
	CPoint vertex3 = { 4, 0 };
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0xFF0000;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	EXPECT_EQ(triangle.GetVertex1().x, vertex1.x);
	EXPECT_EQ(triangle.GetVertex1().y, vertex1.y);
	EXPECT_EQ(triangle.GetVertex2().x, vertex2.x);
	EXPECT_EQ(triangle.GetVertex2().y, vertex2.y);
	EXPECT_EQ(triangle.GetVertex3().x, vertex3.x);
	EXPECT_EQ(triangle.GetVertex3().y, vertex3.y);

	EXPECT_DOUBLE_EQ(triangle.GetArea(), 6.0);
	EXPECT_DOUBLE_EQ(triangle.GetPerimeter(), 12.0);

	EXPECT_EQ(triangle.GetOutlineColor(), outlineColor);
	EXPECT_EQ(triangle.GetFillColor(), fillColor);

	std::string expectedString = std::format("{}: Vertex1: ({}, {}) Vertex2: ({}, {}) Vertex3: ({}, {}) OutlineColor: {:08x} FillColor: {:08x}",
		CTriangle::NAME, vertex1.x, vertex1.y, vertex2.x, vertex2.y, vertex3.x, vertex3.y, outlineColor, fillColor);

	EXPECT_EQ(triangle.ToString(), expectedString);
}

TEST(CTriangleTest, ConstructorFromStringAndGetters)
{
	CTriangle triangle("triangle 0 0 0 3 4 0 0xFF0000 0xFF0000");

	EXPECT_EQ(triangle.GetVertex1().x, 0);
	EXPECT_EQ(triangle.GetVertex1().y, 0);
	EXPECT_EQ(triangle.GetVertex2().x, 0);
	EXPECT_EQ(triangle.GetVertex2().y, 3);
	EXPECT_EQ(triangle.GetVertex3().x, 4);
	EXPECT_EQ(triangle.GetVertex3().y, 0);

	EXPECT_DOUBLE_EQ(triangle.GetArea(), 6.0);
	EXPECT_DOUBLE_EQ(triangle.GetPerimeter(), 12.0);

	EXPECT_EQ(triangle.GetOutlineColor(), 0xFF0000);
	EXPECT_EQ(triangle.GetFillColor(), 0xFF0000);

	std::string expectedString = std::format("{}: Vertex1: ({}, {}) Vertex2: ({}, {}) Vertex3: ({}, {}) OutlineColor: {:08x} FillColor: {:08x}",
		CTriangle::NAME, 0, 0, 0, 3, 4, 0, 0xFF0000, 0xFF0000);

	EXPECT_EQ(triangle.ToString(), expectedString);
}

TEST(CTriangleTest, ConstructorFromInvalidStringInvalidParameterCount)
{
	EXPECT_THROW(CTriangle("triangle 0 0 0 3 4 0 0xFF0000"), std::invalid_argument);
}

TEST(CTriangleTest, ConstructorFromInvalidStringInvalidName)
{
	EXPECT_THROW(CTriangle("shape 0 0 0 3 4 0 0xFF0000 0xFF0000"), std::invalid_argument);
}

TEST(CTriangleTest, ConstructorFromInvalidParameters)
{
	EXPECT_THROW(CTriangle({ 0, 0 }, { 0, 3 }, { -4, 0 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CTriangle({ 0, 0 }, { -4, 0 }, { 0, 3 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CTriangle({ -4, 0 }, { 0, 3 }, { 0, 0 }, 0xFF0000, 0xFF0000), std::invalid_argument);

	EXPECT_THROW(CTriangle({ 0, 0 }, { 0, 0 }, { 0, 0 }, 0xFF0000, 0xFF0000), std::invalid_argument);
}

TEST(CTriangleTest, ConstructorFromInvalidStringInvalidCoordinates)
{
	EXPECT_THROW(CTriangle("triangle 0 0 0 3 -4 0 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CTriangle("triangle 0 0 -4 0 0 3 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CTriangle("triangle -4 0 0 3 0 0 0xFF0000 0xFF0000"), std::invalid_argument);

	EXPECT_THROW(CTriangle("triangle a 0 0 3 4 0 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CTriangle("triangle 0 0 b 3 4 0 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CTriangle("triangle 0 0 0 c 4 0 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CTriangle("triangle 0 0 0 3 d 0 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CTriangle("triangle 0 0 0 3 4 e 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CTriangle("triangle 0 0 0 3 4 0 fxFF0000 0xFF0000"), std::invalid_argument);
}

TEST(CTriangleTest, ConstructorFromInvalidStringInvalidOutlineColor)
{
	EXPECT_THROW(CTriangle("triangle 0 0 0 3 4 0 0xFF0000"), std::invalid_argument);
}
