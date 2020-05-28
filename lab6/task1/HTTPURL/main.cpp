#include "stdafx.h"
#include "UrlParsingError.h"
#include "HTTPURL.h"

void PrintUrlInfo(const CHttpUrl & url)
{
	std::string protocol;
	if (url.GetProtocol() == Protocol::HTTP)
	{
		protocol = "http";
	}
	else
	{
		protocol = "https";
	}
	std::cout << "URL: " << url.GetURL() << std::endl;
	std::cout << "Protocol: " << protocol << std::endl;
	std::cout << "Domain: " << url.GetDomain() << std::endl;
	std::cout << "Document: " << url.GetDocument() << std::endl;
	std::cout << "Port: " << url.GetPort() << std::endl;
	std::cout << std::endl;
}

int main()
{
	std::string inputStr;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "Enter a URL: \n";
		getline(std::cin, inputStr);
		try
		{
			CHttpUrl url(inputStr);
			PrintUrlInfo(url);
		}
		catch (CUrlParsingError& err)
		{
			std::cout << err.what() << std::endl;
		}
	}
	return 0;
}