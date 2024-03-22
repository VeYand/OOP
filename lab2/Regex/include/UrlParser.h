#include <string>

#ifndef REGEX_INCLUDE_URLPARSER_H
#define REGEX_INCLUDE_URLPARSER_H

enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);

#endif // REGEX_INCLUDE_URLPARSER_H
