#include <gtest/gtest.h>
#include "../include/HTMLDecode.h"

TEST (html_decode, decode_with_all_entities)
{
	std::string encodedHTML = "&lt;Hello&gt; &quot;World&quot;!&amp;&apos;";
	std::string expectedDecodedHTML = "<Hello> \"World\"!&'";
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));
}

TEST (html_decode, decode_all_entities_together)
{
	std::string encodedHTML = "&lt;&gt;&quot;&amp;&apos;";
	std::string expectedDecodedHTML = "<>\"&'";
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));
}

TEST (html_decode, decode_with_invalid_entities)
{
	std::string encodedHTML = "&lt&gt&quot&amp&apos";
	std::string expectedDecodedHTML = "&lt&gt&quot&amp&apos";
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));

	encodedHTML = "lt;gt;quot;amp;apos;";
	expectedDecodedHTML = "lt;gt;quot;amp;apos;";
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));

	encodedHTML = "&ltgt;quot;&quotamp;apos;";
	expectedDecodedHTML = "&ltgt;quot;&quotamp;apos;";
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));

	encodedHTML = "&lt;&&&&gt;&quot;&amp;&&&&apos;";
	expectedDecodedHTML = "<&&&>\"&&&&'";
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));

	encodedHTML = "&lt;&gt;;;;;&quot;&amp;&&&&apos;;;";
	expectedDecodedHTML = "<>;;;;\"&&&&';;";
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));
}

TEST (html_decode, decode_empty_html)
{
	std::string encodedHTML;
	std::string expectedDecodedHTML;
	EXPECT_EQ(expectedDecodedHTML, HtmlDecode(encodedHTML));
}

GTEST_API_ int main (int argc, char **argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}