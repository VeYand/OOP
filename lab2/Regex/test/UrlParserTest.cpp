#include <gtest/gtest.h>
#include "../include/UrlParser.h"

TEST (url_parser, url_without_port)
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";


	bool isUrlValid = ParseURL(url, protocol, port, host, document);

	EXPECT_TRUE(isUrlValid);
	EXPECT_EQ(Protocol::HTTP, protocol);
	EXPECT_EQ(80, port);
	EXPECT_EQ("www.mysite.com", host);
	EXPECT_EQ("docs/document1.html?page=30&lang=en#title", document);
}

TEST (url_parser, fully_filled_url)
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url = "https://localhost:3000/docs/document1.html?page=30&lang=en#title";

	bool isUrlValid = ParseURL(url, protocol, port, host, document);

	EXPECT_TRUE(isUrlValid);
	EXPECT_EQ(Protocol::HTTPS, protocol);
	EXPECT_EQ(3000, port);
	EXPECT_EQ("localhost", host);
	EXPECT_EQ("docs/document1.html?page=30&lang=en#title", document);
}

TEST (url_parser, url_without_port_and_without_document)
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url = "ftp://www.mysite.com";

	bool isUrlValid = ParseURL(url, protocol, port, host, document);

	EXPECT_TRUE(isUrlValid);
	EXPECT_EQ(Protocol::FTP, protocol);
	EXPECT_EQ(21, port);
	EXPECT_EQ("www.mysite.com", host);
	EXPECT_TRUE(document.empty());
}

TEST (url_parser, url_with_upper_case_protocol)
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url = "HTTP://localhost";

	bool isUrlValid = ParseURL(url, protocol, port, host, document);

	EXPECT_TRUE(isUrlValid);
	EXPECT_EQ(Protocol::HTTP, protocol);
	EXPECT_EQ(80, port);
	EXPECT_EQ("localhost", host);
	EXPECT_TRUE(document.empty());
}

TEST (url_parser, invalid_port)
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url = "https://localhost:999999999";

	bool isUrlValid = ParseURL(url, protocol, port, host, document);

	EXPECT_FALSE(isUrlValid);
}

TEST (url_parser, invalid_protocol)
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	std::string url = "httpss://localhost";

	bool isUrlValid = ParseURL(url, protocol, port, host, document);

	EXPECT_FALSE(isUrlValid);
}

GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}