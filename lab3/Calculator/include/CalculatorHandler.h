#ifndef CALCULATOR_SRC_CALCULATORHANDLER_H
#define CALCULATOR_SRC_CALCULATORHANDLER_H

#include "Calculator.h"

class CalculatorHandler
{
public:
	void RunCalculator();

private:
	void HandleVarCommand(const std::string& commandLine);
	void HandleLetCommand(const std::string& commandLine);
	void HandleFnCommand(const std::string& commandLine);
	void HandlePrintCommand(const std::string& commandLine);
	void HandlePrintVarsCommand(const std::string& commandLine);
	void HandlePrintFunctionsCommand(const std::string& commandLine);
	static void PrintCalculatorInfo();
	Calculator m_calculator;
};

#endif // CALCULATOR_SRC_CALCULATORHANDLER_H
