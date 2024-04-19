#include <cmath>
#include <format>
#include <gtest/gtest.h>
#include "../include/ShapeFactory.h"

TEST(ShapeFactoryTest, ConstructorFromInvalidStringInvalidName)
{
	std::string str = "cylinder 0 0 5.0 FF0000 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(str), std::invalid_argument);
}

TEST(ShapeFactoryTest, CircleConstructor)
{
	EXPECT_NO_THROW(ShapeFactory::constructShape("circle 0 0 5.0 FF0000 00FF00"));
}

TEST(ShapeFactoryTest, CircleConstructorFromInvalidStringInvalidParameterCount)
{

	std::string circleString = "circle 0 0 5.0 FF0000";

	EXPECT_THROW(ShapeFactory::constructShape(circleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, CircleConstructorFromInvalidStringInvalidCoordinates)
{
	std::string circleString = "circle invalid 0 5.0 FF0000 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(circleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, CircleConstructorFromInvalidStringInvalidOutlineColor)
{
	std::string circleString = "circle 0 0 5.0 invalid 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(circleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, LineSegmentConstructor)
{
	EXPECT_NO_THROW(ShapeFactory::constructShape("line_segment 0 0 3 4 FF0000"));
}

TEST(ShapeFactoryTest, LineSegmentConstructorFromInvalidStringInvalidParameterCount)
{
	std::string lineString = "line_segment 0 0 3 4";

	EXPECT_THROW(ShapeFactory::constructShape(lineString), std::invalid_argument);
}

TEST(ShapeFactoryTest, LineSegmentConstructorFromInvalidStringInvalidName)
{
	std::string lineString = "line 0 0 3 4 FF0000";

	EXPECT_THROW(ShapeFactory::constructShape(lineString), std::invalid_argument);
}

TEST(ShapeFactoryTest, LineSegmentConstructorFromInvalidStringInvalidCoordinates)
{
	std::string lineString = "line_segment invalid 0 3 4 FF0000";

	EXPECT_THROW(ShapeFactory::constructShape(lineString), std::invalid_argument);
}

TEST(ShapeFactoryTest, LineSegmentConstructorFromInvalidStringInvalidOutlineColor)
{
	std::string lineString = "line_segment 0 0 3 4 invalid";

	EXPECT_THROW(ShapeFactory::constructShape(lineString), std::invalid_argument);
}


TEST(ShapeFactoryTest, CRectangleConstructor)
{
	EXPECT_NO_THROW(ShapeFactory::constructShape("rectangle 0 10 20 0 FF0000 00FF00"));
}

TEST(ShapeFactoryTest, CRectangleConstructorFromInvalidStringInvalidParameterCount)
{
	std::string rectangleString = "rectangle 0 10 20 FF0000 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(rectangleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, CRectangleConstructorFromInvalidStringInvalidCoordinates)
{
	std::string rectangleString = "rectangle invalid 10 20 0 FF0000 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(rectangleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, CRectangleConstructorFromInvalidStringInvalidOutlineColor)
{
	std::string rectangleString = "rectangle 0 10 20 0 invalid 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(rectangleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, CTriangleConstructorFromStringAndGetters)
{
	EXPECT_NO_THROW(ShapeFactory::constructShape("triangle 0 0 3 0 0 4 FF0000 00FF00"));
}

TEST(ShapeFactoryTest, CTriangleConstructorFromInvalidStringInvalidParameterCount)
{
	std::string triangleString = "triangle 0 0 3 0 0 4 FF0000";

	EXPECT_THROW(ShapeFactory::constructShape(triangleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, CTriangleConstructorFromInvalidStringInvalidCoordinates)
{
	std::string triangleString = "triangle invalid 0 3 0 0 4 FF0000 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(triangleString), std::invalid_argument);
}

TEST(ShapeFactoryTest, CTriangleConstructorFromInvalidStringInvalidOutlineColor)
{
	std::string triangleString = "triangle 0 0 3 0 0 4 invalid 00FF00";

	EXPECT_THROW(ShapeFactory::constructShape(triangleString), std::invalid_argument);
}