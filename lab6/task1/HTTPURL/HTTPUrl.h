#pragma once

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:

	CHttpUrl(std::string const& url);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	void ParseUrl(std::string const& url);
	Protocol GetProtocol(const std::string& protocol);
	unsigned short GetPort(const std::string& portStr);	
	std::string ComponeURL();

	static std::string GetDocument(std::string document);
private:
	std::string m_URL;
	std::string m_document;
	std::string m_domain;
	Protocol m_protocol;
	unsigned short m_port;
};
