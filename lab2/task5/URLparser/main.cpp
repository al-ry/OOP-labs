#include "stdafx.h"
#include "URLparser.h"

using namespace std;

int main()
{
	string url;
	cout << "Enter a URL: " << endl;
	while (getline(cin, url))
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		if (!ParseURL(url, protocol, port, host, document))
		{
			cout << "Incorrect data. Cannot parse: " << url << endl;
		}
		else
		{
			PrintURLInfo(url, port, host, document);
		}
		cout << "Enter a URL: " << endl;
	}
	return 0;
}
