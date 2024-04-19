#include "../include/CTriangle.h"
#include <gtest/gtest.h>

TEST(CTriangleTest, ConstructorFromParametersAndGetters)
{
	CPoint vertex1(0, 0);
	CPoint vertex2(3, 0);
	CPoint vertex3(0, 4);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	EXPECT_EQ(triangle.GetVertex1().x, vertex1.x);
	EXPECT_EQ(triangle.GetVertex1().y, vertex1.y);
	EXPECT_EQ(triangle.GetVertex2().x, vertex2.x);
	EXPECT_EQ(triangle.GetVertex2().y, vertex2.y);
	EXPECT_EQ(triangle.GetVertex3().x, vertex3.x);
	EXPECT_EQ(triangle.GetVertex3().y, vertex3.y);
	EXPECT_EQ(triangle.GetOutlineColor(), outlineColor);
	EXPECT_EQ(triangle.GetFillColor(), fillColor);
}

TEST(CTriangleTest, ConstructorFromInvalidParameters)
{
	EXPECT_THROW(CTriangle triangle(CPoint(0, 0), CPoint(3, 0), CPoint(0, 0), 0xFF0000, 0x00FF00), std::invalid_argument);
}

TEST(CTriangleTest, GetArea)
{
	CPoint vertex1(0, 0);
	CPoint vertex2(3, 0);
	CPoint vertex3(0, 4);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	EXPECT_DOUBLE_EQ(triangle.GetArea(), 6);
}

TEST(CTriangleTest, GetPerimeter)
{
	CPoint vertex1(0, 0);
	CPoint vertex2(3, 0);
	CPoint vertex3(0, 4);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	EXPECT_DOUBLE_EQ(triangle.GetPerimeter(), 12);
}

TEST(CTriangleTest, ToString)
{
	CPoint vertex1(0, 0);
	CPoint vertex2(3, 0);
	CPoint vertex3(0, 4);
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	std::string expectedString = "CTriangle: Vertex1: (0, 0) Vertex2: (3, 0) Vertex3: (0, 4) OutlineColor: 00ff0000 FillColor: 0000ff00 Area: 6.00 Perimeter: 12.00";

	EXPECT_EQ(triangle.ToString(), expectedString);
}

TEST(CRectangleTest, DegenerateTriangle)
{
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0x00FF00;

	EXPECT_THROW(CTriangle(CPoint(0, 0), CPoint(0, 0), CPoint(0, 0), outlineColor, fillColor), std::invalid_argument);
	EXPECT_THROW(CTriangle(CPoint(0, 0), CPoint(0, 0), CPoint(1, 1), outlineColor, fillColor), std::invalid_argument);
	EXPECT_THROW(CTriangle(CPoint(1, 1), CPoint(0, 0), CPoint(0, 0), outlineColor, fillColor), std::invalid_argument);
	EXPECT_THROW(CTriangle(CPoint(0, 0), CPoint(1, 1), CPoint(0, 0), outlineColor, fillColor), std::invalid_argument);
}