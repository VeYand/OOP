#include <utility>
#include "../include/Function.h"


Function::Function(std::string functionIdentifier, Function::Operation operation, std::string firstIdentifier, std::string secondIdentifier)
	: m_identifier(std::move(functionIdentifier))
	, m_operation(operation)
	, m_firstIdentifier(std::move(firstIdentifier))
	, m_secondIdentifier(std::move(secondIdentifier))
{
}

std::string Function::GetName()
{
	return m_identifier;
}

Function::Operation Function::GetOperation()
{
	return m_operation;
}

std::string Function::GetFirstIdentifier()
{
	return m_firstIdentifier;
}

std::string Function::GetSecondIdentifier()
{
	return m_secondIdentifier;
}
