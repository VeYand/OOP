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
	[[nodiscard]] std::string GetName() const;
	[[nodiscard]] Operation GetOperation() const;
	[[nodiscard]] std::string GetFirstIdentifier() const;
	[[nodiscard]] std::string GetSecondIdentifier() const;

private:
	std::string m_identifier;
	Operation m_operation;
	std::string m_firstIdentifier;
	std::string m_secondIdentifier;
};

#endif // CALCULATOR_SRC_FUNCTION_H
