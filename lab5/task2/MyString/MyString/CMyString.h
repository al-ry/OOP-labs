#pragma once

class CMyString
{
public:
	template <bool IsConst>
	class CIterator
	{
		friend class CIterator<true>;
		friend CMyString;
		CIterator(char* pChars)
			: m_pValue(pChars){};

	public:
		using MyType = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const char*, char*>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;
		CIterator() = default;

		char& operator*() const
		{
			return *m_pValue;
		}
		MyType operator--()
		{
			return --m_pValue;
		}
		MyType operator++()
		{
			return ++m_pValue;
		}
		bool operator==(const MyType& other)
		{
			return m_pValue == other.m_pValue;
		}
		bool operator!=(const MyType& other)
		{
			return m_pValue != other.m_pValue;
		}
		MyType operator-=(difference_type offset)
		{
			m_pValue -= offset;
			return *this;
		}
		MyType operator+=(difference_type offset)
		{
			m_pValue += offset;
			return *this;
		}
		difference_type operator-(const CIterator& other)
		{
			return (m_pValue - other.m_pValue);
		}
	private:
		char* m_pValue;
	};

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;



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
	char *m_pChars = nullptr;
	size_t m_length = 0;
};

CMyString operator+(const CMyString& lStr, const CMyString& rStr);
CMyString operator+(const char * lPStr, const CMyString& rStr);
CMyString operator+(const std::string& lStlStr, const CMyString& rStr);

bool operator==(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator!=(const CMyString& lCmpStr, const CMyString& rCmpStr);

bool operator<(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator>=(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator>(const CMyString& lCmpStr, const CMyString& rCmpStr);
bool operator<=(const CMyString& lCmpStr, const CMyString& rCmpStr);


std::ostream& operator<<(std::ostream& stream, CMyString const& str);
std::istream& operator>>(std::istream& stream, CMyString & str);
