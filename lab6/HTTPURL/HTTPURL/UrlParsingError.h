#pragma once

#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(const std::string& msg);
};