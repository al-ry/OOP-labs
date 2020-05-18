#include "stdafx.h"
#include "CMyString.h"


void CMyString::CreateString()
{
	try
	{
		m_pChars = new char[m_length + 1];
		m_pChars[m_length] = '\0';
	}
	catch (std::bad_alloc const & ba)
	{
		std::cout << "bad_alloc caught: " << ba.what() << '\n';
	}
}
CMyString::CMyString()
	: CMyString("", 0)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_length = length;
	CreateString();
	std::memcpy(m_pChars, pString, length);	
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.m_pChars, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_pChars(other.m_pChars)
	, m_length(other.m_length)
{
	other.m_pChars = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length()) 
{
}

CMyString::~CMyString()
{
	delete[] m_pChars;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pChars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start > m_length)
	{
		throw std::out_of_range("Out of range");
	}
	if (length == SIZE_MAX || length >= m_length)
	{
		return CMyString(&m_pChars[start], m_length - start);
	}
	else
	{
		return CMyString(&m_pChars[start], length);
	}
}

void CMyString::Clear()
{
	delete[] m_pChars;
	m_length = 0;
	CreateString();
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (&other != this)
	{
		CMyString tmpCpy(other);
		std::swap(m_pChars, tmpCpy.m_pChars);
		std::swap(m_length, tmpCpy.m_length);
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (&other != this)
	{
		Clear();
		m_pChars = other.m_pChars;
		m_length = other.m_length;
		other.m_pChars = nullptr;
		other.m_length = 0;
	}
	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	assert(index < m_length);
	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
	assert(index < m_length);
	return m_pChars[index];
}



CMyString const operator+(const CMyString& lStr, const CMyString& rStr)
{
	size_t newLen = lStr.GetLength() + rStr.GetLength();
	auto newStr = new char[newLen + 1];
	newStr[newLen] = '\0';

	std::memcpy(newStr, lStr.GetStringData(), lStr.GetLength());
	std::memcpy(newStr + lStr.GetLength(), rStr.GetStringData(), rStr.GetLength());

	CMyString newMyStr = CMyString(newStr, newLen);
	delete[] newStr;
	return newMyStr;
}

CMyString& CMyString::operator+=(const CMyString& rStr)
{
	*this = *this + rStr;
	return *this;
}

CMyString const operator+(const char* lPStr, const CMyString& rStr)
{
	CMyString newStr = CMyString(lPStr) + rStr;
	return newStr;
}

CMyString const operator+(const std::string& lStlStr, const CMyString& rStr)
{
	CMyString newStr = CMyString(lStlStr) + rStr;
	return newStr;
}

bool operator==(const CMyString& lCmpStr, const CMyString& rCmpStr)
{
	return (lCmpStr.GetLength() == rCmpStr.GetLength()
		&& std::memcmp(lCmpStr.GetStringData(), rCmpStr.GetStringData(), lCmpStr.GetLength()) == 0);
}

bool operator!=(const CMyString& lCmpStr, const CMyString& rCmpStr)
{
	return !(lCmpStr == rCmpStr);
}

bool operator<(const CMyString& lCmpStr, const CMyString& rCmpStr)
{
	int cmpRes = std::memcmp(lCmpStr.GetStringData(), rCmpStr.GetStringData(), lCmpStr.GetLength());
	if (cmpRes == 0 || cmpRes > 0)
	{
		return false;
	}
	return true;
}

bool operator>=(const CMyString& lCmpStr, const CMyString& rCmpStr)
{
	return !(lCmpStr < rCmpStr);
}


bool operator>(const CMyString& lCmpStr, const CMyString& rCmpStr)
{
	int cmpRes = std::memcmp(lCmpStr.GetStringData(), rCmpStr.GetStringData(), lCmpStr.GetLength());
	if (cmpRes == 0 || cmpRes < 0)
	{
		return false;
	}
	return true;
}

bool operator<=(const CMyString& lCmpStr, const CMyString& rCmpStr)
{
	return !(lCmpStr > rCmpStr);
}

std::ostream& operator<<(std::ostream& stream, CMyString const& str)
{
	stream << str.GetStringData();
	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& str)
{
	char charsBuffer[255];
	stream.getline(charsBuffer, sizeof(charsBuffer));
	str = charsBuffer;
	return stream;
}


