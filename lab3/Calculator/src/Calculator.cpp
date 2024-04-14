#include "../include/Calculator.h"
#include <format>

void Calculator::DeclareVariable(const std::string& identifier)
{
	if (m_functionMap.contains(identifier) || m_variableMap.contains(identifier))
	{
		throw std::invalid_argument("Identifier already exists");
	}

	m_variableMap[identifier] = std::make_unique<Variable>(identifier, NAN);
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

void Calculator::InitVariable(const std::string& identifier,
	const std::string& identifierToInstall)
{
	if (identifier == identifierToInstall)
	{
		throw std::invalid_argument("Variable cannot refer to itself");
	}

	auto function = m_functionMap.find(identifier);

	if (m_functionMap.find(identifier) != m_functionMap.end())
	{
		m_variableMap[identifier] = std::make_unique<Variable>(identifier,
			CalculateFunctionValue(function->first));
		return;
	}

	auto value = CalculateValue(identifierToInstall);
	m_variableMap[identifier] = std::make_unique<Variable>(identifier, value);
}

void Calculator::CreateFunction(const std::string& funcIdentifier, const std::string& varIdentifier)
{
	if (m_functionMap.contains(funcIdentifier) || m_variableMap.contains(funcIdentifier))
	{
		throw std::invalid_argument("Identifier already exists");
	}

	m_functionMap[funcIdentifier] = std::make_unique<Function>(funcIdentifier,
		Function::Operation::IDENTITY, varIdentifier);
}

void Calculator::CreateFunction(const std::string& funcIdentifier, Function::Operation operation, const std::string& firstIdentifier, const std::string& secondIdentifier)
{
	if (m_functionMap.contains(funcIdentifier) || m_variableMap.contains(funcIdentifier))
	{
		throw std::invalid_argument("Identifier already exists");
	}

	m_functionMap[funcIdentifier] = std::make_unique<Function>(
		funcIdentifier, operation, firstIdentifier, secondIdentifier);
}

double Calculator::CalculateValue(const std::string& identifier) const
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

double Calculator::CalculateFunctionValue(const std::string& identifier) const
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

	auto firstValue = CalculateValue(firstIdentifier);
	if (std::isnan(firstValue))
	{
		return NAN;
	}
	auto secondValue = CalculateValue(secondIdentifier);
	if (std::isnan(secondValue))
	{
		return NAN;
	}

	switch (operation)
	{
	case Function::MULTIPLICATION:
		return firstValue * secondValue;
	case Function::DIVISION:
		return firstValue / secondValue;
	case Function::ADDITION:
		return firstValue + secondValue;
	case Function::SUBTRACTION:
		return firstValue - secondValue;
	default:
		break;
	}

	return NAN;
}

std::map<std::string, double> Calculator::GetVars() const
{
	std::map<std::string, double> varValues;
	for (const auto& variable : m_variableMap)
	{
		varValues[variable.first] = variable.second->GetValue();
	}
	return varValues;
}

std::map<std::string, double> Calculator::GetFuncs() const
{
	std::map<std::string, double> funcValues;
	for (const auto& function : m_functionMap)
	{
		funcValues[function.first] = CalculateFunctionValue(function.first);
	}
	return funcValues;
}
