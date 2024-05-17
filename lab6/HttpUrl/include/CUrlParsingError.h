#ifndef HTTPURL_CURLPARSINGERROR_H
#define HTTPURL_CURLPARSINGERROR_H

#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError()
		: std::invalid_argument(BASE_MESSAGE), m_message(BASE_MESSAGE)
	{
	}

	explicit CUrlParsingError(const std::string& message)
		: std::invalid_argument(message), m_message(message)
	{
	}

	[[nodiscard]] const char* what() const noexcept override
	{
		return m_message.c_str();
	}

private:
	constexpr static const char* BASE_MESSAGE = "Url parsing error";
	std::string m_message;
};

#endif // HTTPURL_CURLPARSINGERROR_H
