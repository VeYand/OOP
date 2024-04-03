#include "../include/Variable.h"
#include <utility>

Variable::Variable(std::string identifier, std::optional<double> value)
	: m_identifier(std::move(identifier))
	, m_value(value)
{
}

std::string Variable::GetIdentifier()
{
	return m_identifier;
}

std::optional<double> Variable::GetValue()
{
	return m_value;
}

void Variable::SetValue(double value)
{
	m_value = value;
}