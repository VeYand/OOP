#include "../include/Calculator.h"
#include <gtest/gtest.h>

TEST(CalculatorTest, DeclareVariable)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	auto vars = calculator.GetVars();
	EXPECT_TRUE(vars.find("x") != vars.end());
	EXPECT_TRUE(std::isnan(calculator.CalculateValue("x")));
}

TEST(CalculatorTest, DeclareAndInitVariableWithValue)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	auto value = calculator.CalculateValue("x");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 5.0);
}

TEST(CalculatorTest, InitVariableWithValue)
{
	Calculator calculator;
	calculator.InitVariable("x", 5.0);
	auto value = calculator.CalculateValue("x");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 5.0);
}

TEST(CalculatorTest, InitVariableWithIdentifier)
{
	Calculator calculator;
	EXPECT_THROW(calculator.InitVariable("x", "y"), std::invalid_argument);
	calculator.InitVariable("y", 10.0);
	calculator.InitVariable("x", "y");
	auto valueX = calculator.CalculateValue("x");
	auto valueY = calculator.CalculateValue("y");

	EXPECT_FALSE(std::isnan(valueX));
	EXPECT_FALSE(std::isnan(valueY));
	EXPECT_DOUBLE_EQ(valueX, 10.0);
	EXPECT_DOUBLE_EQ(valueY, 10.0);
}

TEST(CalculatorTest, CreateFunctionWithVariable)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.CreateFunction("f", "x");
	auto value = calculator.CalculateValue("f");
	EXPECT_TRUE(std::isnan(value));
	calculator.InitVariable("x", 5.0);
	value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 5.0);
}

TEST(CalculatorTest, CreateFunctionWithMultOperation)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f",
		Function::Operation::MULTIPLICATION, "x", "x");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 25.0);
}

TEST(CalculatorTest, CreateFunctionWithAddOperation)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f",
		Function::Operation::ADDITION, "x", "x");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 10.0);
}

TEST(CalculatorTest, CreateFunctionWithDivizionOperation)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f",
		Function::Operation::DIVISION, "x", "x");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 1.0);
}

TEST(CalculatorTest, CreateFunctionWithSubtractionOperation)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.InitVariable("y", 100.0);
	calculator.CreateFunction("f",
		Function::Operation::SUBTRACTION, "x", "y");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, -95.0);
}

TEST(CalculatorTest, DivideByZero)
{
	Calculator calculator;
	calculator.InitVariable("x", 5.0);
	calculator.InitVariable("y", 0);
	calculator.CreateFunction("f",
		Function::Operation::DIVISION, "x", "y");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, INFINITY);
}

TEST(CalculatorTest, DivideByInf)
{
	Calculator calculator;
	calculator.InitVariable("x", 5.0);
	calculator.InitVariable("y", INFINITY);
	calculator.CreateFunction("f",
		Function::Operation::DIVISION, "x", "y");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 0.0);
}

TEST(CalculatorTest, MultByZero)
{
	Calculator calculator;
	calculator.InitVariable("x", 5.0);
	calculator.InitVariable("y", 0);
	calculator.CreateFunction("f",
		Function::Operation::MULTIPLICATION, "x", "y");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, 0.0);
}

TEST(CalculatorTest, MultByInf)
{
	Calculator calculator;
	calculator.InitVariable("x", 5.0);
	calculator.InitVariable("y", INFINITY);
	calculator.CreateFunction("f",
		Function::Operation::MULTIPLICATION, "x", "y");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(std::isnan(value));
	EXPECT_DOUBLE_EQ(value, INFINITY);
}

TEST(CalculatorTest, DeclaringVariableWithFunctionName)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f",
		Function::Operation::MULTIPLICATION, "x", "x");

	calculator.InitVariable("result", "f");
	auto result = calculator.CalculateValue("result");
	EXPECT_FALSE(std::isnan(result));
	EXPECT_DOUBLE_EQ(result, 25.0);
}

TEST(CalculatorTest, RedeclaringFunction)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f",
		Function::Operation::MULTIPLICATION, "x", "x");
	EXPECT_THROW(calculator.CreateFunction("f",
					 Function::Operation::DIVISION, "x", "x"),
		std::invalid_argument);
}

TEST(CalculatorTest, GetVars)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	auto vars = calculator.GetVars();
	EXPECT_EQ(vars.size(), 1);
	EXPECT_TRUE(vars.contains("x"));
	EXPECT_DOUBLE_EQ(vars["x"], 5.0);
}

TEST(CalculatorTest, GetFuncs)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f", "x");
	auto funcs = calculator.GetFuncs();
	EXPECT_EQ(funcs.size(), 1);
	EXPECT_TRUE(funcs.contains("f"));
	EXPECT_DOUBLE_EQ(funcs["f"], 5.0);
}

TEST(CalculatorTest, IdentifierNotExists)
{
	Calculator calculator;
	EXPECT_THROW(calculator.CalculateValue("identifier"), std::invalid_argument);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}