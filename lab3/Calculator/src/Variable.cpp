#include "../include/Variable.h"
#include <utility>

Variable::Variable(std::string identifier, double value)
	: m_identifier(std::move(identifier))
	, m_value(value)
{
}

std::string Variable::GetIdentifier() const
{
	return m_identifier;
}

double Variable::GetValue() const
{
	return m_value;
}

void Variable::SetValue(double value)
{
	m_value = value;
}