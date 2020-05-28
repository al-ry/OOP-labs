#include "stdafx.h"
#include "UrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& msg)
	: std::invalid_argument(msg)
{
}
