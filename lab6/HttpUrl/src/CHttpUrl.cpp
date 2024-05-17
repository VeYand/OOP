#include "../include/CHttpUrl.h"
#include "../include/CUrlParsingError.h"
#include <algorithm>
#include <format>
#include <limits>
#include <regex>
#include <string>

namespace
{
std::string ToLower(const std::string& str)
{
	std::string newStr = str;
	std::transform(newStr.begin(), newStr.end(), newStr.begin(), ::tolower);
	return newStr;
}

void AddSlashIfMissing(std::string& str)
{
	if (str.empty() || str[0] != '/')
	{
		str = '/' + str;
	}
}
} // namespace

const std::string CHttpUrl::PROTOCOL_REGEXP = R"((https?))";
const std::string CHttpUrl::HOST_REGEXP = R"(([^:/]+))";
const std::string CHttpUrl::PORT_REGEXP = R"((\d+))";
const std::string CHttpUrl::DOCUMENT_REGEXP = R"((?:/(.*))?)";

const std::string CHttpUrl::URL_REGEXP
	= std::format(
		R"({}://{}(?::{})?{})",
		PROTOCOL_REGEXP,
		HOST_REGEXP,
		PORT_REGEXP,
		DOCUMENT_REGEXP);

unsigned short CHttpUrl::GetDefaultPort(CHttpUrl::Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return HTTP_PROTOCOL_DEFAULT_PORT;
	case Protocol::HTTPS:
		return HTTPS_PROTOCOL_DEFAULT_PORT;
	default:
		throw CUrlParsingError("Invalid url protocol");
	}
}

std::string CHttpUrl::GetProtocolString(CHttpUrl::Protocol protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return HTTP_PROTOCOL_STRING;
	case Protocol::HTTPS:
		return HTTPS_PROTOCOL_STRING;
	default:
		throw CUrlParsingError("Invalid url protocol");
	}
}

CHttpUrl::Protocol CHttpUrl::StringToProtocol(const std::string& protocolStr)
{
	std::string lowerProtocolStr = ToLower(protocolStr);
	if (lowerProtocolStr == HTTP_PROTOCOL_STRING)
	{
		return Protocol::HTTP;
	}
	else if (lowerProtocolStr == HTTPS_PROTOCOL_STRING)
	{
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Invalid url protocol");
}

void CHttpUrl::CheckUrlHost(const std::string& hostStr)
{
	if (hostStr.empty())
	{
		throw CUrlParsingError("Invalid url host");
	}
}

unsigned short CHttpUrl::ParseURLPort(const std::string& portStr, CHttpUrl::Protocol& protocol)
{
	if (portStr.empty())
	{
		return GetDefaultPort(protocol);
	}

	int portNum;
	try
	{
		portNum = std::stoi(portStr);
		if (portNum < 0 || portNum > std::numeric_limits<unsigned short>::max())
		{
			throw CUrlParsingError("Invalid url port");
		}

		return static_cast<unsigned short>(portNum);
	}
	catch (const std::out_of_range& e)
	{
		throw CUrlParsingError("Invalid url port");
	}
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::smatch match;
	std::regex urlRegex(URL_REGEXP, std::regex::icase);

	try
	{
		if (!std::regex_match(url, match, urlRegex))
		{
			throw CUrlParsingError("Invalid url");
		}
	}
	catch (const std::regex_error&)
	{
		throw CUrlParsingError("Invalid url");
	}

	CheckUrlHost(match[2]);

	auto protocol = StringToProtocol(match[1]);
	auto host = match[2];
	auto port = ParseURLPort(match[3], protocol);
	auto document = match[4].str();

	AddSlashIfMissing(document);

	m_domain = std::move(host);
	m_protocol = protocol;
	m_port = port;
	m_document = std::move(document);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, CHttpUrl::Protocol protocol)
{
	CheckUrlHost(domain);

	m_document = document;
	AddSlashIfMissing(m_document);

	m_domain = domain;
	m_protocol = protocol;
	m_port = GetDefaultPort(protocol);
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, CHttpUrl::Protocol protocol, unsigned short port)
{
	CheckUrlHost(domain);

	m_document = document;
	AddSlashIfMissing(m_document);

	m_domain = domain;
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	if (GetDefaultPort(m_protocol) != m_port)
	{
		return std::format("{}://{}:{}{}", GetProtocolString(m_protocol), m_domain, m_port, m_document);
	}

	return std::format("{}://{}{}", GetProtocolString(m_protocol), m_domain, m_document);
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

CHttpUrl::Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
