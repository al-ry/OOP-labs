#pragma once


enum class Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
void PrintURLInfo(const std::string& url, int port, const std::string& host, const std::string& document);
