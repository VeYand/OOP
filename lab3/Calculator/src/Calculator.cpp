#include "../include/Calculator.h"
#include <format>

void Calculator::DeclareVariable(const std::string& identifier)
{
	if (m_functionMap.find(identifier) != m_functionMap.end()
		|| m_variableMap.find(identifier) != m_variableMap.end())
	{
		throw std::invalid_argument("Variable already exists");
	}

	m_variableMap[identifier] = std::make_unique<Variable>(identifier, std::nullopt);
}

void Calculator::InitVariable(const std::string& identifier, double value)
{
	auto variable = m_variableMap.find(identifier);

	if (m_variableMap.find(identifier) == m_variableMap.end())
	{
		m_variableMap[identifier] = std::make_unique<Variable>(identifier, value);
		return;
	}

	variable->second->SetValue(value);
}

void Calculator::InitVariable(const std::string& identifier, const std::string& identifierToInstall)
{
	if (identifier == identifierToInstall)
	{
		throw std::invalid_argument("Variable cannot refer to itself");
	}

	auto function = m_functionMap.find(identifier);

	if (m_functionMap.find(identifier) != m_functionMap.end())
	{
		m_variableMap[identifier] = std::make_unique<Variable>(identifier, CalculateFunctionValue(function->first));
		return;
	}

	auto variable = m_variableMap.find(identifier);
	auto value = CalculateValue(identifierToInstall);
	m_variableMap[identifier] = std::make_unique<Variable>(identifier, value);
}

void Calculator::CreateFunction(const std::string& funcIdentifier, const std::string& varIdentifier)
{
	m_functionMap[funcIdentifier] = std::make_unique<Function>(funcIdentifier, Function::Operation::IDENTITY, varIdentifier);
}

void Calculator::CreateFunction(const std::string& funcIdentifier, Function::Operation operation, const std::string& firstIdentifier, const std::string& secondIdentifier)
{
	m_functionMap[funcIdentifier] = std::make_unique<Function>(funcIdentifier, operation, firstIdentifier, secondIdentifier);
}

std::optional<double> Calculator::CalculateValue(const std::string& identifier)
{
	auto variable = m_variableMap.find(identifier);

	if (variable != m_variableMap.end())
	{
		return variable->second->GetValue();
	}

	auto function = m_functionMap.find(identifier);

	if (function != m_functionMap.end())
	{
		return CalculateFunctionValue(identifier);
	}

	throw std::invalid_argument(std::format("Identifier `{}` not exists", identifier));
}

std::optional<double> Calculator::CalculateFunctionValue(const std::string& identifier)
{
	auto function = m_functionMap.find(identifier);

	if (function == m_functionMap.end())
	{
		throw std::invalid_argument(std::format("Function `{}` not exists", identifier));
	}

	auto operation = function->second->GetOperation();

	auto firstIdentifier = function->second->GetFirstIdentifier();
	auto secondIdentifier = function->second->GetSecondIdentifier();

	if (operation == Function::Operation::IDENTITY)
	{
		return CalculateValue(firstIdentifier);
	}

	std::optional<double> result;
	std::optional<double> firstValue;
	std::optional<double> secondValue;

	firstValue = CalculateValue(firstIdentifier);
	if (!firstValue.has_value())
	{
		return std::nullopt;
	}
	secondValue = CalculateValue(secondIdentifier);
	if (!secondValue.has_value())
	{
		return std::nullopt;
	}

	switch (operation)
	{
	case Function::MULTIPLICATION:
		return firstValue.value() * secondValue.value();
	case Function::DIVISION:
		return firstValue.value() / secondValue.value();
	case Function::ADDITION:
		return firstValue.value() + secondValue.value();
	case Function::SUBTRACTION:
		return firstValue.value() - secondValue.value();
	default:
		break;
	}

	return std::nullopt;
}

std::map<std::string, std::optional<double>> Calculator::GetVars()
{
	std::map<std::string, std::optional<double>> varValues;
	for (const auto& variable : m_variableMap)
	{
		varValues[variable.first] = variable.second->GetValue();
	}
	return varValues;
}

std::map<std::string, std::optional<double>> Calculator::GetFuncs()
{
	std::map<std::string, std::optional<double>> funcValues;
	for (const auto& function : m_functionMap)
	{
		funcValues[function.first] = CalculateFunctionValue(function.first);
	}
	return funcValues;
}
