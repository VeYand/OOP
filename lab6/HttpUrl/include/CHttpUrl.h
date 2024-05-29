#ifndef HTTPURL_CHTTPURL_H
#define HTTPURL_CHTTPURL_H

#include <format>
#include <string>

class CHttpUrl
{
public:
	enum class Protocol
	{
		HTTP,
		HTTPS
	};

	explicit CHttpUrl(std::string const& url);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	[[nodiscard]] std::string GetURL() const;
	[[nodiscard]] std::string GetDomain() const;
	[[nodiscard]] std::string GetDocument() const;
	[[nodiscard]] Protocol GetProtocol() const;
	[[nodiscard]] unsigned short GetPort() const;

private:
	static unsigned short GetDefaultPort(CHttpUrl::Protocol protocol);
	static std::string GetProtocolString(CHttpUrl::Protocol protocol);
	static Protocol StringToProtocol(const std::string& protocolStr);
	static void CheckUrlHost(const std::string& hostStr);
	static unsigned short ParseURLPort(const std::string& portStr, Protocol& protocol);

	constexpr static const std::string HTTP_PROTOCOL_STRING = "http";
	constexpr static const std::string HTTPS_PROTOCOL_STRING = "https";
	constexpr static const int HTTP_PROTOCOL_DEFAULT_PORT = 80;
	constexpr static const int HTTPS_PROTOCOL_DEFAULT_PORT = 443;
	constexpr static const unsigned short MAX_PORT_NUM = 65535;
	constexpr static const unsigned short MIN_PORT_NUM = 1;
	static const std::string PROTOCOL_REGEXP;
	static const std::string HOST_REGEXP;
	static const std::string PORT_REGEXP;
	static const std::string DOCUMENT_REGEXP;
	static const std::string URL_REGEXP;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};

#endif // HTTPURL_CHTTPURL_H
