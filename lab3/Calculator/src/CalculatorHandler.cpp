#include "../include/CalculatorHandler.h"
#include <format>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{
const std::string VAR_COMMAND = "var";
const std::string LET_COMMAND = "let";
const std::string FN_COMMAND = "fn";
const std::string PRINT_COMMAND = "print";
const std::string PRINT_VARS_COMMAND = "printvars";
const std::string PRINT_FUNCTIONS_COMMAND = "printfns";

const char MULTIPLICATION_OPERATION = '*';
const char DIVISION_OPERATION = '/';
const char ADDITION_OPERATION = '+';
const char SUBTRACTION_OPERATION = '-';

const char EQUALS_SYMBOL = '=';
const std::string NAN_STRING = "nan";

const std::string WHITESPACE = " \n\r\t\f\v";

std::string Trim(std::string str)
{
	size_t start = str.find_first_not_of(WHITESPACE);
	size_t end = str.find_last_not_of(WHITESPACE);

	if (start != std::string::npos && end != std::string::npos)
	{
		str = str.substr(start, end - start + 1);
		return str;
	}

	if (start != std::string::npos)
	{
		str = str.substr(start);
		return str;
	}

	if (end != std::string::npos)
	{
		str = str.substr(0, end + 1);
	}
	return str;
}
} // namespace

void CalculatorHandler::RunCalculator()
{
	PrintCalculatorInfo();
	std::string commandLine;
	while (std::getline(std::cin, commandLine))
	{
		std::istringstream iss(commandLine);
		std::string command;
		iss >> command;
		if (command == VAR_COMMAND)
		{
			HandleVarCommand(commandLine);
		}
		else if (command == LET_COMMAND)
		{
			HandleLetCommand(commandLine);
		}
		else if (command == FN_COMMAND)
		{
			HandleFnCommand(commandLine);
		}
		else if (command == PRINT_COMMAND)
		{
			HandlePrintCommand(commandLine);
		}
		else if (command == PRINT_VARS_COMMAND)
		{
			HandlePrintVarsCommand();
		}
		else if (command == PRINT_FUNCTIONS_COMMAND)
		{
			HandlePrintFunctionsCommand();
		}
		else
		{
			std::cout << std::format("Unknown command: {}", command) << std::endl;
		}
	}
}

void CalculatorHandler::HandleVarCommand(const std::string& commandLine)
{
	std::istringstream iss(commandLine);
	std::string command;
	iss >> command;

	if (command != VAR_COMMAND)
	{
		std::cout << "Invalid command name" << std::endl;
		return;
	}

	std::string identifier;
	if (!(iss >> identifier))
	{
		std::cout << "Cannot read identifier name" << std::endl;
		return;
	}

	try
	{
		m_calculator.DeclareVariable(Trim(identifier));
	}
	catch (const std::invalid_argument& e) // inalid argument
	{
		std::cout << e.what() << std::endl;
	}
}

void CalculatorHandler::HandleLetCommand(const std::string& commandLine)
{
	std::istringstream iss(commandLine);
	std::string command;
	iss >> command;

	if (command != LET_COMMAND)
	{
		std::cout << "Invalid command name" << std::endl;
		return;
	}

	std::string identifier;
	if (!std::getline(iss, identifier, EQUALS_SYMBOL))
	{
		std::cout << "Cannot read identifier name" << std::endl;
		return;
	}
	std::string valueString;
	if (!(iss >> valueString))
	{
		std::cout << "Cannot read value" << std::endl;
		return;
	}

	try
	{
		double value = std::stod(valueString);
		m_calculator.InitVariable(Trim(identifier), value);
		m_calculator.InitVariable(Trim(identifier), Trim(valueString));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool ContainsSymbol(const std::string& str, char symbol)
{
	return str.find(symbol) != std::string::npos;
}

void CalculatorHandler::HandleFnCommand(const std::string& commandLine)
{
	std::istringstream iss(commandLine);
	std::string command;
	iss >> command;

	if (command != FN_COMMAND)
	{
		std::cout << "Invalid command name" << std::endl;
		return;
	}

	std::string identifier;

	if (!std::getline(iss, identifier, EQUALS_SYMBOL))
	{
		std::cout << "Cannot read identifier name" << std::endl;
		return;
	}
	std::string bodyString;
	if (!std::getline(iss, bodyString))
	{
		std::cout << "Cannot read function body" << std::endl;
		return;
	}

	std::istringstream iBodyStream(bodyString);

	std::string firstIdentifier, secondIdentifier;
	Function::Operation operation = Function::Operation::IDENTITY;

	std::map<char, Function::Operation> operationMap = {
		{ MULTIPLICATION_OPERATION, Function::Operation::MULTIPLICATION },
		{ DIVISION_OPERATION, Function::Operation::DIVISION },
		{ ADDITION_OPERATION, Function::Operation::ADDITION },
		{ SUBTRACTION_OPERATION, Function::Operation::SUBTRACTION }
	};

	for (const auto& [operatorSymbol, fnOperation] : operationMap)
	{
		if (ContainsSymbol(bodyString, operatorSymbol))
		{
			operation = fnOperation;
			if (!std::getline(iBodyStream, firstIdentifier, operatorSymbol))
			{
				std::cout << "Cannot read first identifier" << std::endl;
				return;
			}
			break;
		}
	}

	if (!(iBodyStream >> secondIdentifier))
	{
		std::cout << (operation == Function::Operation::IDENTITY ? "Cannot read first identifier" : "Cannot read second identifier") << std::endl;
		return;
	}

	try
	{
		if (operation == Function::Operation::IDENTITY)
		{
			m_calculator.CreateFunction(Trim(identifier), Trim(secondIdentifier));
		}
		else
		{
			m_calculator.CreateFunction(
				Trim(identifier), operation, Trim(firstIdentifier), Trim(secondIdentifier));
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CalculatorHandler::HandlePrintCommand(const std::string& commandLine)
{
	std::istringstream iss(commandLine);
	std::string command;
	iss >> command;

	if (command != PRINT_COMMAND)
	{
		std::cout << "Invalid command name" << std::endl;
		return;
	}

	std::string identifier;
	if (!(iss >> identifier))
	{
		std::cout << "Cannot read identifier name" << std::endl;
		return;
	}

	try
	{
		auto value = m_calculator.CalculateValue(Trim(identifier));
		if (!std::isnan(value))
		{
			std::cout << std::fixed << std::setprecision(2) << value << std::endl;
		}
		else
		{
			std::cout << NAN_STRING << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void CalculatorHandler::HandlePrintVarsCommand()
{
	auto variables = m_calculator.GetVars();
	for (const auto& [identifier, value] : variables)
	{
		std::cout << identifier << ":" << std::fixed << std::setprecision(2)
				  << (std::isnan(value) ? NAN_STRING : std::to_string(value)) << std::endl;
	}
}

void CalculatorHandler::HandlePrintFunctionsCommand()
{
	auto functions = m_calculator.GetFuncs();
	for (const auto& [identifier, value] : functions)
	{
		std::cout << identifier << ":" << std::fixed << std::setprecision(2)
				  << (std::isnan(value) ? NAN_STRING : std::to_string(value)) << std::endl;
	}
}

void CalculatorHandler::PrintCalculatorInfo()
{
	std::cout << "Calculator supports the following operations:" << std::endl;
	std::cout << std::format("1. Variable declaration: {} <identifier>", VAR_COMMAND) << std::endl;
	std::cout << std::format("2. Assignment of numerical value to a variable: {} <identifier> = <floating-point number>", LET_COMMAND) << std::endl;
	std::cout << std::format("3. Assignment of the value of another variable to a variable: {} <identifier1> = <identifier2>", LET_COMMAND) << std::endl;
	std::cout << std::format("4. Declaration of a function with one argument: {} <identifier1> = <identifier2>", FN_COMMAND) << std::endl;
	std::cout << std::format("5. Declaration of a function with two arguments and an operation: {} <identifier1> = <identifier2><operation><identifier3>", FN_COMMAND) << std::endl;
	std::cout << std::format("6. Output of the value of a variable or function: {} <identifier>", PRINT_COMMAND) << std::endl;
	std::cout << std::format("7. Output of all declared variables and their values: {}", PRINT_VARS_COMMAND) << std::endl;
	std::cout << std::format("8. Output of all declared functions and their values: {}", PRINT_FUNCTIONS_COMMAND) << std::endl;
}
