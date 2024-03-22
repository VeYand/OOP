#include <unordered_map>
#include <stdexcept>
#include <string>

const std::string DECODED_DOUBLE_QUOTE_SYMBOL = "\"";
const std::string DECODED_APOSTROPHE_SYMBOL = "'";
const std::string DECODED_SIGN_LESS_SYMBOL = "<";
const std::string DECODED_SIGN_MORE_SYMBOL = ">";
const std::string DECODED_AMPERSAND_SYMBOL = "&";
const char SEMICOLON_SYMBOL = ';';
const char AMPERSAND_SYMBOL = '&';
const std::string ENCODED_DOUBLE_QUOTATION = "&quot;";
const std::string ENCODED_APOSTROPHE = "&apos;";
const std::string ENCODED_SIGN_LESS = "&lt;";
const std::string ENCODED_SIGN_MORE = "&gt;";
const std::string ENCODED_AMPERSAND = "&amp;";

std::string DecodeSymbol(const std::string& subject)
{
	std::unordered_map<std::string, std::string> decodeMap = {
		{ ENCODED_DOUBLE_QUOTATION, DECODED_DOUBLE_QUOTE_SYMBOL },
		{ ENCODED_APOSTROPHE, DECODED_APOSTROPHE_SYMBOL },
		{ ENCODED_SIGN_LESS, DECODED_SIGN_LESS_SYMBOL },
		{ ENCODED_SIGN_MORE, DECODED_SIGN_MORE_SYMBOL },
		{ ENCODED_AMPERSAND, DECODED_AMPERSAND_SYMBOL }
	};

	if (decodeMap.find(subject) == decodeMap.end())
	{
		throw std::invalid_argument("Unknown symbol " + subject);
	}

	return decodeMap[subject];
}

std::string HtmlDecode(const std::string& html)
{
	std::string result;
	for (size_t i = 0; i < html.size(); ++i)
	{
		if (html[i] != AMPERSAND_SYMBOL)
		{
			result += html[i];
			continue;
		}

		auto semicolonFoundPos = html.find(SEMICOLON_SYMBOL, i);

		if (semicolonFoundPos == std::string::npos)
		{
			result += html[i];
			continue;
		}

		auto subject = html.substr(i, semicolonFoundPos - i + 1);

		std::string decodedString;
		try
		{
			decodedString = DecodeSymbol(subject);
		}
		catch (const std::invalid_argument& e)
		{
			result += html[i];
			continue;
		}

		result += decodedString;
		i = semicolonFoundPos;
	}

	return result;
}