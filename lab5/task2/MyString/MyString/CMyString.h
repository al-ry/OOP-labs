#pragma once
class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	CMyString(std::string const& stlString);
	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();


	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other) noexcept;
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	CMyString& operator+=(const CMyString& rStr);

private:
	void CreateString();
private:
	char *m_pChars = nullptr;
	size_t m_length = 0 ;
};

CMyString const operator+(const CMyString& lStr, const CMyString& rStr);
CMyString const operator+(const char * lPStr, const CMyString& rStr);
CMyString const operator+(const std::string& lStlStr, const CMyString& rStr);

bool operator==(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator!=(const CMyString& lCmpStr, const CMyString& rCmpStr);

bool operator<(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator>=(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator>(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator<=(const CMyString& lCmpStr, const CMyString& rCmpStr);


std::ostream& operator<<(std::ostream& stream, CMyString const& str);
std::istream& operator>>(std::istream& stream, CMyString & str);
