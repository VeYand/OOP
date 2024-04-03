#ifndef CALCULATOR_SRC_FUNCTION_H
#define CALCULATOR_SRC_FUNCTION_H

#include <string>

class Function
{
public:
	enum Operation
	{
		MULTIPLICATION,
		DIVISION,
		ADDITION,
		SUBTRACTION,
		IDENTITY
	};
	Function(std::string functionIdentifier, Operation operation, std::string firstIdentifier, std::string secondIdentifier = "");
	std::string GetName();
	Operation GetOperation();
	std::string GetFirstIdentifier();
	std::string GetSecondIdentifier();

private:
	std::string m_identifier;
	Operation m_operation;
	std::string m_firstIdentifier;
	std::string m_secondIdentifier;
};

#endif // CALCULATOR_SRC_FUNCTION_H
