#include "include/HTMLDecode.h"
#include <iostream>

void DecodeHTMLStream()
{
	std::string line;
	while (std::cin >> line)
	{
		std::cout << HtmlDecode(line) << std::endl;
	}
}

int main()
{
	DecodeHTMLStream();

	return 0;
}
