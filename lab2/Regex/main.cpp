#include "include/UrlParser.h"
#include <format>
#include <iostream>

void ParseUrlStream()
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	std::string line;
	while (std::getline(std::cin, line)) {
		if (ParseURL(line, protocol, port, host, document)) {
			std::cout << line << std::endl;
			std::cout << std::format("HOST: {}", host) << std::endl;
			std::cout << std::format("PORT: {}", port) << std::endl;
			std::cout << std::format("DOC: {}", document) << std::endl;
		} else {
			std::cout << "URL is invalid" << std::endl;
		}
	}
}

int main()
{
	ParseUrlStream();

	return 0;
}
