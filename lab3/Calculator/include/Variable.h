#ifndef CALCULATOR_SRC_VARIABLE_H
#define CALCULATOR_SRC_VARIABLE_H

#include <optional>
#include <string>
#include <cmath>

class Variable
{
public:
	explicit Variable(std::string identifier, double value = NAN);
	[[nodiscard]] std::string GetIdentifier() const;
	[[nodiscard]] double GetValue() const;
	void SetValue(double value);

private:
	std::string m_identifier;
	double m_value = NAN;
};

#endif // CALCULATOR_SRC_VARIABLE_H
