#ifndef CALCULATOR_SRC_VARIABLE_H
#define CALCULATOR_SRC_VARIABLE_H

#include <optional>
#include <string>

class Variable
{
public:
	Variable(std::string identifier, std::optional<double> value = std::nullopt);
	std::string GetIdentifier();
	std::optional<double> GetValue();
	void SetValue(double value);

private:
	std::string m_identifier;
	std::optional<double> m_value = std::nullopt;
};

#endif // CALCULATOR_SRC_VARIABLE_H
