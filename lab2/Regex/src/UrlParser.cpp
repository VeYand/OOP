#include "../include/UrlParser.h"
#include <iostream>
#include <regex>

const std::string HTTP_PROTOCOL_STRING = "http";
const std::string HTTPS_PROTOCOL_STRING = "https";
const std::string FTP_PROTOCOL_STRING = "ftp";
const int HTTP_PROTOCOL_DEFAULT_PORT = 80;
const int HTTPS_PROTOCOL_DEFAULT_PORT = 443;
const int FTP_PROTOCOL_DEFAULT_PORT = 21;
const int MINIMAL_PORT_VALUE = 1;
const int MAXIMAL_PORT_VALUE = 65535;

std::string ToLower(const std::string& str)
{
	std::string newStr = str;
	std::transform(newStr.begin(), newStr.end(), newStr.begin(), ::tolower);
	return newStr;
}

bool ParseURLProtocol(const std::string& protocolStr, Protocol& protocol)
{
	std::string lowerProtocolStr = ToLower(protocolStr);
	if (lowerProtocolStr == HTTP_PROTOCOL_STRING)
	{
		protocol = Protocol::HTTP;
		return true;
	}
	else if (lowerProtocolStr == HTTPS_PROTOCOL_STRING)
	{
		protocol = Protocol::HTTPS;
		return true;
	}
	else if (lowerProtocolStr == FTP_PROTOCOL_STRING)
	{
		protocol = Protocol::FTP;
		return true;
	}

	return false;
}

bool ParseURLHost(const std::string& hostStr, std::string& host)
{
	if (hostStr.empty())
	{
		return false;
	}

	host = hostStr;
	return true;
}

bool ParseURLPort(const std::string& portStr, Protocol& protocol, int& port)
{
	if (portStr.empty())
	{
		switch (protocol)
		{
		case Protocol::HTTP:
			port = HTTP_PROTOCOL_DEFAULT_PORT;
			return true;
		case Protocol::HTTPS:
			port = HTTPS_PROTOCOL_DEFAULT_PORT;
			return true;
		case Protocol::FTP:
			port = FTP_PROTOCOL_DEFAULT_PORT;
			return true;
		default:
			return false;
		}
	}

	int portNum;
	try
	{
		portNum = std::stoi(portStr);
	}
	catch (const std::out_of_range& e)
	{
		return false;
	}

	if (portNum < MINIMAL_PORT_VALUE || portNum > MAXIMAL_PORT_VALUE)
	{
		return false;
	}

	port = portNum;

	return true;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex urlRegex(R"((https?|ftp)://([^:/]+)(?::(\d+))?(?:/(.*))?)", std::regex::icase);
	std::smatch match;

	Protocol parsedProtocol;
	int parsedPort;
	std::string parsedHost;

	if (!std::regex_match(url, match, urlRegex))
	{
		return false;
	}
	if (!ParseURLProtocol(match[1], parsedProtocol))
	{
		return false;
	}
	if (!ParseURLHost(match[2], parsedHost))
	{
		return false;
	}
	if (!ParseURLPort(match[3], parsedProtocol, parsedPort))
	{
		return false;
	}

	protocol = parsedProtocol;
	host = parsedHost;
	port = parsedPort;
	document = match[4];

	return true;
}