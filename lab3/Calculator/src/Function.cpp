#include <utility>
#include "../include/Function.h"


Function::Function(std::string functionIdentifier, Function::Operation operation, std::string firstIdentifier, std::string secondIdentifier)
	: m_identifier(std::move(functionIdentifier))
	, m_operation(operation)
	, m_firstIdentifier(std::move(firstIdentifier))
	, m_secondIdentifier(std::move(secondIdentifier))
{
}

std::string Function::GetName() const
{
	return m_identifier;
}

Function::Operation Function::GetOperation() const
{
	return m_operation;
}

std::string Function::GetFirstIdentifier() const
{
	return m_firstIdentifier;
}

std::string Function::GetSecondIdentifier() const
{
	return m_secondIdentifier;
}
