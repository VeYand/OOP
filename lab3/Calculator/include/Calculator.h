#ifndef CALCULATOR_SRC_CALCULATOR_H
#define CALCULATOR_SRC_CALCULATOR_H

#include "./Function.h"
#include "./Variable.h"
#include <map>
#include <memory>

using VariableMap = std::map<std::string, std::unique_ptr<Variable>>;
using FunctionMap = std::map<std::string, std::unique_ptr<Function>>;

class Calculator
{
public:
	void DeclareVariable(const std::string& identifier);
	void InitVariable(const std::string& identifier, double value);
	void InitVariable(const std::string& identifier, const std::string& identifierToInstall);
	void CreateFunction(const std::string& funcIdentifier, const std::string& varIdentifier);
	void CreateFunction(const std::string& funcIdentifier, Function::Operation operation,
		const std::string& firstIdentifier, const std::string& secondIdentifier);
	[[nodiscard]] double CalculateValue(const std::string& identifier) const;
	[[nodiscard]] std::map<std::string, double> GetVars() const;
	[[nodiscard]] std::map<std::string, double> GetFuncs() const;

private:
	[[nodiscard]] double CalculateFunctionValue(const std::string& identifier) const;
	VariableMap m_variableMap;
	FunctionMap m_functionMap;
};

#endif // CALCULATOR_SRC_CALCULATOR_H
