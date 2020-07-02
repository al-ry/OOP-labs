#include "stdafx.h"
#include "HTTPUrl.h"
#include "UrlParsingError.h"
#include <boost/algorithm/string/trim_all.hpp>
#include <iostream>

const int MAX_PORT = 65535;
const char SLASH = '/';
enum Matches
{
	url,
	protocol,
	domain,
	port,
	document
};

const std::map<Protocol, int> DEFAULT_PORTS = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 }
};

namespace
{
bool IsPortInRange(int port)
{
	return port >= 1 && port <= MAX_PORT;
}
bool IsDomainCorrect(const std::string& domain)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain cannot be empty");
	}
	if (!std::all_of(domain.begin(), domain.end(), [](char ch) {
			return std::isdigit(ch) || std::isalpha(ch) || ch == '.' || ch == '-';
		}))
	{
		throw std::invalid_argument("There are invalid symbols in domain");
	}
	return true;
}
unsigned short GetDefaultPort(Protocol protocol)
{
	auto defaultProtocol = DEFAULT_PORTS.find(protocol);
	return defaultProtocol->second;
}
} // namespace

CHttpUrl::CHttpUrl(std::string const& url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
	m_URL = ComponeURL();
}

CHttpUrl::CHttpUrl(std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port)
{
	if (IsDomainCorrect(domain))
	{
		m_domain = domain;
	}
	m_document = GetDocument(document);
	m_protocol = protocol;
	m_port = port;
	m_URL = ComponeURL();
}

std::string CHttpUrl::GetURL() const
{
	return m_URL;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

void CHttpUrl::ParseUrl(std::string const& url)
{
	std::smatch match;
	std::string copyOfURL(url);
	std::regex reg(R"(^(\w+):\/\/([^\s:\/]+)?(?::(\d+))?(?:\/(\S*))?$)");
	if (!regex_search(copyOfURL, match, reg))
	{
		throw(CUrlParsingError("Invalid URL"));
	}
	m_URL = match[Matches::url];
	m_protocol = GetProtocol(match[Matches::protocol]);
	m_domain = match[Matches::domain];
	m_port = GetPort(match[Matches::port]);
	std::string document = match[Matches::document];
	m_document = SLASH + document;
}

Protocol CHttpUrl::GetProtocol(const std::string& protocol)
{
	std::string lowerCaseProtocol = protocol;
	std::transform(lowerCaseProtocol.begin(), lowerCaseProtocol.end(), lowerCaseProtocol.begin(), tolower);
	if (lowerCaseProtocol == "http")
	{
		return m_protocol = Protocol::HTTP;
	}
	else if (lowerCaseProtocol == "https")
	{
		return m_protocol = Protocol::HTTPS;
	}
	throw(CUrlParsingError("Invalid URL protocol"));
}

unsigned short CHttpUrl::GetPort(const std::string& portStr)
{
	int port;
	if (!portStr.empty())
	{
		port = std::stoi(portStr);
		if (IsPortInRange(port))
		{
			return port;
		}
		else
		{
			throw CUrlParsingError("Out of range port");
		}
	}
	return GetDefaultPort(m_protocol);
}

std::string CHttpUrl::ComponeURL()
{
	std::string strProtocol;
	if (GetProtocol() == Protocol::HTTP)
	{
		strProtocol = "http";
	}
	else if (GetProtocol() == Protocol::HTTPS)
	{
		strProtocol = "https";
	}
	return strProtocol + "://" + GetDomain() + GetDocument();
}

std::string CHttpUrl::GetDocument(std::string document)
{
	if (!document.empty())
	{
		if (document[0] != SLASH)
		{
			return SLASH + document;
		}
		return document;
	}
	return SLASH + document;
}
