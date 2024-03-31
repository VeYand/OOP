#include "../include/CRectangle.h"
#include <format>
#include <gtest/gtest.h>

TEST(CRectangleTest, ConstructorFromParametersAndGetters)
{
	CPoint leftTop = { 3, 4 };
	CPoint rightBottom = { 5, 3 };
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0xFF0000;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

	EXPECT_EQ(rectangle.GetLeftTop().x, leftTop.x);
	EXPECT_EQ(rectangle.GetLeftTop().y, leftTop.y);
	EXPECT_EQ(rectangle.GetRightBottom().x, rightBottom.x);
	EXPECT_EQ(rectangle.GetRightBottom().y, rightBottom.y);

	EXPECT_EQ(rectangle.GetOutlineColor(), outlineColor);
	EXPECT_EQ(rectangle.GetFillColor(), fillColor);
}

TEST(CRectangleTest, ConstructorFromStringAndGetters)
{
	CRectangle rectangle("rectangle 3 4 5 3 0xFF0000 0xFF0000");

	EXPECT_EQ(rectangle.GetLeftTop().x, 3);
	EXPECT_EQ(rectangle.GetLeftTop().y, 4);
	EXPECT_EQ(rectangle.GetRightBottom().x, 5);
	EXPECT_EQ(rectangle.GetRightBottom().y, 3);

	EXPECT_EQ(rectangle.GetOutlineColor(), 0xFF0000);
	EXPECT_EQ(rectangle.GetFillColor(), 0xFF0000);
}

TEST(CRectangleTest, ConstructorFromInvalidStringInvalidParameterCount)
{
	EXPECT_THROW(CRectangle("rectangle 3 4 5 3 0xFF0000"), std::invalid_argument);
}

TEST(CRectangleTest, ConstructorFromInvalidStringInvalidName)
{
	EXPECT_THROW(CRectangle("shape 3 4 5 3 0xFF0000 0xFF0000"), std::invalid_argument);
}

TEST(CRectangleTest, ConstructorFromInvalidParametersInvalidCoordinates)
{
	EXPECT_THROW(CRectangle({ 3, 4 }, { 3, 3 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CRectangle({ 3, 4 }, { 2, 3 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CRectangle({ 3, 4 }, { 5, 4 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CRectangle({ 3, 4 }, { 3, 5 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CRectangle({ -1, 4 }, { 0, 3 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CRectangle({ 1, -1 }, { 2, -3 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CRectangle({ -3, 4 }, { -1, 3 }, 0xFF0000, 0xFF0000), std::invalid_argument);
	EXPECT_THROW(CRectangle({ 2, 4 }, { 0, -1 }, 0xFF0000, 0xFF0000), std::invalid_argument);
}

TEST(CRectangleTest, ConstructorFromInvalidStringInvalidCoordinates)
{
	EXPECT_THROW(CRectangle("rectangle 3 4 3 3 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CRectangle("rectangle 3 4 2 3 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CRectangle("rectangle 3 4 5 4 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CRectangle("rectangle 3 4 3 5 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CRectangle("rectangle -1 4 0 3 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CRectangle("rectangle 1 -1 2 -3 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CRectangle("rectangle -3 4 -1 3 0xFF0000 0xFF0000"), std::invalid_argument);
	EXPECT_THROW(CRectangle("rectangle 2 4 0 -1 0xFF0000 0xFF0000"), std::invalid_argument);
}

TEST(CRectangleTest, ConstructorFromInvalidStringInvalidOutlineColor)
{
	EXPECT_THROW(CRectangle("rectangle 3 4 4 3 invalid invalid"), std::invalid_argument);
}

TEST(CRectangleTest, AreaAndPerimeter)
{
	CPoint leftTop = { 3, 4 };
	CPoint rightBottom = { 5, 3 };
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0xFF0000;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

	EXPECT_DOUBLE_EQ(rectangle.GetArea(), 2.0);

	EXPECT_DOUBLE_EQ(rectangle.GetPerimeter(), 6.0);
}

TEST(CRectangleTest, ToString)
{
	CPoint leftTop = { 3, 4 };
	CPoint rightBottom = { 5, 3 };
	uint32_t outlineColor = 0xFF0000;
	uint32_t fillColor = 0xFF0000;

	CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

	std::string expectedString = std::format("{}: LeftTop: ({}, {}) RightBottom: ({}, {}) OutlineColor: {:08x} FillColor: {:08x}",
		CRectangle::NAME, leftTop.x, leftTop.y, rightBottom.x, rightBottom.y, outlineColor, fillColor);

	EXPECT_EQ(rectangle.ToString(), expectedString);
}