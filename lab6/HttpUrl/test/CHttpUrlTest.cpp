#include "../include/CHttpUrl.h"
#include "../include/CUrlParsingError.h"
#include <gtest/gtest.h>


TEST(CHttpUrl, ValidUrlWithoutPort)
{
	std::string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";

	auto httpUrl = CHttpUrl(url);

	EXPECT_EQ(url, httpUrl.GetURL());
	EXPECT_EQ(CHttpUrl::Protocol::HTTP, httpUrl.GetProtocol());
	EXPECT_EQ(80, httpUrl.GetPort());
	EXPECT_EQ("www.mysite.com", httpUrl.GetDomain());
	EXPECT_EQ("/docs/document1.html?page=30&lang=en#title", httpUrl.GetDocument());
}

TEST(CHttpUrl, FullyFilledUrl)
{
	std::string url = "https://localhost:3000/docs/document1.html?page=30&lang=en#title";

	auto httpUrl = CHttpUrl(url);

	EXPECT_EQ(url, httpUrl.GetURL());
	EXPECT_EQ(CHttpUrl::Protocol::HTTPS, httpUrl.GetProtocol());
	EXPECT_EQ(3000, httpUrl.GetPort());
	EXPECT_EQ("localhost", httpUrl.GetDomain());
	EXPECT_EQ("/docs/document1.html?page=30&lang=en#title", httpUrl.GetDocument());
}

TEST(CHttpUrl, UrlWithoutPortAndWithoutDocument)
{
	std::string url = "https://www.mysite.com";

	auto httpUrl = CHttpUrl(url);

	EXPECT_EQ("https://www.mysite.com/", httpUrl.GetURL());
	EXPECT_EQ(CHttpUrl::Protocol::HTTPS, httpUrl.GetProtocol());
	EXPECT_EQ(443, httpUrl.GetPort());
	EXPECT_EQ("www.mysite.com", httpUrl.GetDomain());
	EXPECT_EQ("/", httpUrl.GetDocument());
}

TEST(CHttpUrl, UrlWithUpperCaseProtocolCHttpUrl)
{
	std::string url = "HTTP://localhost";

	auto httpUrl = CHttpUrl(url);

	EXPECT_EQ("http://localhost/", httpUrl.GetURL());
	EXPECT_EQ(CHttpUrl::Protocol::HTTP, httpUrl.GetProtocol());
	EXPECT_EQ(80, httpUrl.GetPort());
	EXPECT_EQ("localhost", httpUrl.GetDomain());
	EXPECT_EQ("/", httpUrl.GetDocument());
}

TEST(CHttpUrl, InvalidProtocol)
{
	EXPECT_THROW(CHttpUrl("httpss://localhost"), CUrlParsingError);
}

TEST(CHttpUrl, ConstructWithCorrectUrl) {
	EXPECT_NO_THROW(CHttpUrl("https://mysite.com"));
}

TEST(CHttpUrl, ConstructWithCorrectUrlAndComplicatedDomain) {
	EXPECT_NO_THROW(CHttpUrl("https://mysite.com/hello/ratings/ping"));
}

TEST(CHttpUrl, ConstructWithCorrectUrlAndDocument) {
	EXPECT_NO_THROW(CHttpUrl("https://mysite.com/status"));
}

TEST(CHttpUrl, ConstructWithUnderflowPort) {
	EXPECT_THROW(CHttpUrl("http://mysite.com:0/status"), std::invalid_argument);
}

TEST(CHttpUrl, ConstructWithCorrectUrlAndMinPort) {
	EXPECT_NO_THROW(CHttpUrl("http://mysite.com:1/status"));
}

TEST(CHttpUrl, ConstructWithOverflowPort) {
	EXPECT_THROW(CHttpUrl("http://mysite.com:65536/status"), std::invalid_argument);
}

TEST(CHttpUrl, ConstructWithCorrectUrlAndMaxPort) {
	EXPECT_NO_THROW(CHttpUrl("https://mysite.com:65535/status"));
}

TEST(CHttpUrl, ConstructWithIncorrectUrlNoProtocol) {
	EXPECT_THROW(CHttpUrl("//mysite.com/mysite"), CUrlParsingError);
}

TEST(CHttpUrl, ConstructWithIncorrectUrlNoDomain) {
	EXPECT_THROW(CHttpUrl("http://"), CUrlParsingError);
}

TEST(CHttpUrl, ConstructWithIncorrectUrlWrongProtocol) {
	EXPECT_THROW(CHttpUrl("abcde://mysite.com/mysite"), CUrlParsingError);
}

TEST(CHttpUrl, ConstructWithIncorrectUrlPortNotNumber) {
	EXPECT_THROW(CHttpUrl("http://mysite.com:string"), CUrlParsingError);
}

TEST(CHttpUrl, ConstructWithIncorrectUrlPortLessThanMinPort) {
	EXPECT_THROW(CHttpUrl("https://mysite.com:123abc"), CUrlParsingError);
}

TEST(CHttpUrl, ConstructWithIncorrectUrlPortGreaterThanMaxPort) {
	EXPECT_THROW(CHttpUrl("http://mysite.com:" + std::to_string(std::numeric_limits<unsigned short>::max() + 1)), CUrlParsingError);
}

TEST(CHttpUrl, ConstructWithCorrectValuesAndEmptyDocument) {
	CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTP;
	std::string domain = "mysite.com";
	std::string document;
	EXPECT_NO_THROW(CHttpUrl(domain, document, protocol));
}

TEST(CHttpUrl, ConstructWithCorrectValuesAndValuedDocument) {
	CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTPS;
	std::string domain = "mysite.com";
	std::string document = "site/ratings";
	EXPECT_NO_THROW(CHttpUrl(domain, document, protocol));
}

TEST(CHttpUrl, ConstructWithCorrectValuesAndRandomPort) {
	CHttpUrl::Protocol protocol = CHttpUrl::Protocol::HTTP;
	std::string domain = "mysite.com";
	std::string document;
	unsigned short port = 52532;
	EXPECT_NO_THROW(CHttpUrl(domain, document, protocol, port));
}

TEST(CHttpUrl, GetMethods) {
	std::string domain = "mysite.com";
	unsigned short port = 4554;
	std::string document = "/hello/world/image.png?";
	std::string correctStringUrl = "https://" + domain + ":" + std::to_string(port) + document;

	CHttpUrl correctUrl(domain, document, CHttpUrl::Protocol::HTTPS, port);

	EXPECT_EQ(correctUrl.GetProtocol(), CHttpUrl::Protocol::HTTPS);
	EXPECT_EQ(correctUrl.GetDomain(), domain);
	EXPECT_EQ(correctUrl.GetDocument(), document);
	EXPECT_EQ(correctUrl.GetPort(), port);
	EXPECT_EQ(correctUrl.GetURL(), correctStringUrl);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}