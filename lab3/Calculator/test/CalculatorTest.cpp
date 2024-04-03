#include "../include/Calculator.h"
#include <gtest/gtest.h>

TEST(CalculatorTest, DeclareVariable)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	auto vars = calculator.GetVars();
	EXPECT_TRUE(vars.find("x") != vars.end());
}

TEST(CalculatorTest, DeclareAndInitVariableWithValue)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	auto value = calculator.CalculateValue("x");
	EXPECT_TRUE(value.has_value());
	EXPECT_DOUBLE_EQ(value.value(), 5.0);
}

TEST(CalculatorTest, InitVariableWithValue)
{
	Calculator calculator;
	calculator.InitVariable("x", 5.0);
	auto value = calculator.CalculateValue("x");
	EXPECT_TRUE(value.has_value());
	EXPECT_DOUBLE_EQ(value.value(), 5.0);
}

TEST(CalculatorTest, InitVariableWithIdentifier)
{
	Calculator calculator;
	EXPECT_THROW(calculator.InitVariable("x", "y"), std::invalid_argument);
	calculator.InitVariable("y", 10.0);
	calculator.InitVariable("x", "y");
	auto valueX = calculator.CalculateValue("x");
	auto valueY = calculator.CalculateValue("y");

	EXPECT_TRUE(valueX.has_value());
	EXPECT_TRUE(valueY.has_value());
	EXPECT_DOUBLE_EQ(valueX.value(), 10.0);
	EXPECT_DOUBLE_EQ(valueY.value(), 10.0);
}

TEST(CalculatorTest, CreateFunctionWithVariable)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.CreateFunction("f", "x");
	auto value = calculator.CalculateValue("f");
	EXPECT_FALSE(value.has_value());
	calculator.InitVariable("x", 5.0);
	value = calculator.CalculateValue("f");
	EXPECT_TRUE(value.has_value());
	EXPECT_DOUBLE_EQ(value.value(), 5.0);
}

TEST(CalculatorTest, CreateFunctionWithOperation)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f", Function::Operation::MULTIPLICATION, "x", "x");
	auto value = calculator.CalculateValue("f");
	EXPECT_TRUE(value.has_value());
	EXPECT_DOUBLE_EQ(value.value(), 25.0);
}

TEST(CalculatorTest, CalculateValueOfVariable)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	auto value = calculator.CalculateValue("x");
	EXPECT_TRUE(value.has_value());
	EXPECT_DOUBLE_EQ(value.value(), 5.0);
}

TEST(CalculatorTest, GetVars)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	auto vars = calculator.GetVars();
	EXPECT_EQ(vars.size(), 1);
	EXPECT_TRUE(vars.find("x") != vars.end());
	EXPECT_DOUBLE_EQ(vars["x"].value(), 5.0);
}

TEST(CalculatorTest, GetFuncs)
{
	Calculator calculator;
	calculator.DeclareVariable("x");
	calculator.InitVariable("x", 5.0);
	calculator.CreateFunction("f", "x");
	auto funcs = calculator.GetFuncs();
	EXPECT_EQ(funcs.size(), 1);
	EXPECT_TRUE(funcs.find("f") != funcs.end());
	EXPECT_DOUBLE_EQ(funcs["f"].value(), 5.0);
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