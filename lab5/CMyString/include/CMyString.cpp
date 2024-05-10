#include "CMyString.h"
#include <cstring>
#include <stdexcept>

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
{
	m_pData = new char[m_length + 1];
	strncpy(m_pData, pString, length);
	m_pData[length] = END_OF_STRING;
}

CMyString::CMyString()
	: CMyString(new char, 0)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_pData(other.m_pData)
	, m_length(other.m_length)
{
	other.m_pData = nullptr;
	other.m_length = 0;
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	delete[] m_pData;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return m_pData;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw std::out_of_range("Start index out of string length");
	}

	if ((start + length) > m_length)
	{
		length = m_length - start;
	}

	return { &m_pData[start], length };
}

void CMyString::Clear()
{
	delete[] m_pData;
	m_pData = new char[1];
	m_pData[0] = END_OF_STRING;
	m_length = 0;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (std::addressof(other) != this)
	{
		CMyString tempCopy(other);
		std::swap(m_pData, tempCopy.m_pData);
		std::swap(m_length, tempCopy.m_length);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (std::addressof(other) != this)
	{
		delete[] m_pData;
		m_length = 0;
		m_pData = nullptr;

		std::swap(m_pData, other.m_pData);
		std::swap(m_length, other.m_length);
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	size_t newCMyStringLength = m_length + other.m_length;

	char* newCMyStringData = new char[newCMyStringLength + 1];
	memcpy(newCMyStringData, m_pData, m_length);
	memcpy(newCMyStringData + m_length, other.m_pData, other.m_length);

	newCMyStringData[newCMyStringLength] = CMyString::END_OF_STRING;

	delete[] m_pData;
	m_pData = newCMyStringData;
	m_length = newCMyStringLength;

	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_pData[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::out_of_range("index is out of range");
	}

	return m_pData[index];
}

CMyString operator+(CMyString const& myString1, CMyString const& myString2)
{
	size_t newCMyStringLength = myString1.GetLength() + myString2.GetLength();
	CMyString newCMyString;

	char* newCMyStringData = new char[newCMyStringLength + 1];
	memcpy(newCMyStringData, myString1.GetStringData(), myString1.GetLength());
	memcpy(newCMyStringData + myString1.GetLength(),
		myString2.GetStringData(),
		myString2.GetLength());
	newCMyStringData[newCMyStringLength] = CMyString::END_OF_STRING;

	newCMyString = CMyString(newCMyStringData, newCMyStringLength);
	delete[] newCMyStringData;

	return newCMyString;
}

CMyString operator+(const std::string& string1, const CMyString& myString2)
{
	return CMyString(string1) + myString2;
}

CMyString operator+(const char* string1, const CMyString& myString2)
{
	return CMyString(string1) + myString2;
}

CMyString operator+(const CMyString& myString1, const std::string& string2)
{
	return myString1 + CMyString(string2);
}

CMyString operator+(const CMyString& myString1, const char* string2)
{
	return myString1 + CMyString(string2);
}

bool operator==(CMyString const& myString1, CMyString const& myString2)
{
	if (myString1.GetLength() != myString2.GetLength())
	{
		return false;
	}

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   myString1.GetLength())
		== 0;
}

bool operator!=(CMyString const& myString1, CMyString const& myString2)
{
	return !(myString1 == myString2);
}

bool operator>(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		> 0;
}

bool operator>=(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		>= 0;
}

bool operator<(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		< 0;
}

bool operator<=(CMyString const& myString1, CMyString const& myString2)
{
	size_t minLength = std::min(myString1.GetLength(), myString2.GetLength());

	return memcmp(myString1.GetStringData(),
			   myString2.GetStringData(),
			   minLength)
		<= 0;
}

std::ostream& operator<<(std::ostream& stream, const CMyString& myString)
{
	stream << myString.GetStringData();

	return stream;
}

std::istream& operator>>(std::istream& stream, CMyString& myString)
{
	size_t resultDataSize = 1;
	size_t resultLength = 0;
	char* resultData = new char[resultDataSize];
	char ch;

	while (
		stream.get(ch)
		&& ch != CMyString::INPUT_STRING_SEPARATOR
		&& ch != CMyString::END_OF_LINE)
	{
		resultData[resultLength] = ch;
		resultLength++;

		if (resultLength == resultDataSize)
		{
			char* newResultData = new char[resultDataSize * 2];
			memcpy(newResultData, resultData, resultDataSize);
			delete[] resultData;
			resultData = newResultData;

			resultDataSize *= 2;
		}
	}

	resultData[resultLength] = CMyString::END_OF_STRING;

	delete[] myString.m_pData;
	myString.m_length = resultLength;
	myString.m_pData = resultData;

	return stream;
}
