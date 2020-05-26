#include "stdafx.h"
#include "URLparser.h"

using namespace std;

const int MAX_PORT = 65535;

const map<Protocol, int> DEFAULT_PORTS = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 }
};

optional<Protocol> GetProtocol(const string& protocolStr)
{
	Protocol protocol;
	string lowerCaseProtocol = protocolStr;
	transform(lowerCaseProtocol.begin(), lowerCaseProtocol.end(), lowerCaseProtocol.begin(), tolower);
	if (lowerCaseProtocol == "http")
	{
		return protocol = Protocol::HTTP;
	}
	else if (lowerCaseProtocol == "https")
	{
		return protocol = Protocol::HTTPS;
	}
	else if (lowerCaseProtocol == "ftp")
	{
		return protocol = Protocol::FTP;
	}
	else
	{
		return nullopt;
	}
}

optional<int> GetPort(const string& portStr, const Protocol& protocol)
{
	int port;
	if (portStr.size())
	{
		try
		{
			port = stoi(portStr);
		}
		catch (exception const& error)
		{
			cout << error.what() << endl;
			return nullopt;
		}
		if (port >= 1 && port <= MAX_PORT)
		{
			return port;
		}
		return nullopt;
	}
	auto defaultProtocol = DEFAULT_PORTS.find(protocol);
	port = defaultProtocol->second;
	return port;
}

bool ParseURL(string const& url, Protocol& protocol, int& port, string& host, string& document)
{
	smatch match;
	regex reg(R"(^(\w+):\/\/([^\s:\/]+)?(?::(\d+))?(?:\/(\S*))?$)");
	if (!regex_search(url, match, reg))
	{
		return false;
	}
	auto isProtocolCorrect = GetProtocol(match[1]);
	if (!isProtocolCorrect)
	{
		cout << "Unknown protocol: " << match[1] << endl;
		return false;
	}
	protocol = isProtocolCorrect.value();
	host = match[2];
	auto isPortCorrect = GetPort(match[3], protocol);
	if (!isPortCorrect)
	{
		cout << "Unknown port: " << match[3] << endl;
		cout << "Port should be in range: 1 <= port >= " << MAX_PORT << endl;
		return false;
	}
	port = isPortCorrect.value();
	document = match[4];

	return true;
}

void PrintURLInfo(const string& url, int port, const string& host, const string& document)
{
	cout << url << endl;
	cout << "HOST: " << host << endl;
	cout << "PORT: " << port << endl;
	cout << "DOC: " << document << endl;
}