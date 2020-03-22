#include "stdafx.h"
#include "URLparser.h"

using namespace std;

int main()
{
	string url;
	while (getline(cin, url))
	{
		Protocol protocol;
		int port;
		string host;
		string document;
		if (!ParseURL(url, protocol, port, host, document))
		{
			cout << "Incorrect data. Cannot parse: " << url << endl; 
			continue;
		}
		PrintURLInfo(url, port, host, document);
	}
	return 0;
}
