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

// конструктор копирования
CMyString::CMyString(const CMyString& other)
	: CMyString(other.GetStringData(), other.GetLength())
{
}

// перемещающий конструктор
CMyString::CMyString(CMyString&& other) noexcept
	: m_pData(other.m_pData)
	, m_length(other.m_length)
{
	other.m_pData = nullptr;
	other.m_length = 0;
}

// конструктор, инициализирующий строку данными из
// строки стандартной библиотеки C++
CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

// деструктор класса - освобождает память, занимаемую символами строки
CMyString::~CMyString()
{
	delete[] m_pData;
}

// возвращает длину строки (без учета завершающего нулевого символа)
size_t CMyString::GetLength() const
{
	return m_length;
}

// возвращает указатель на массив символов строки.
// В конце массива обязательно должен быть завершающий нулевой символ
// даже если строка пустая
const char* CMyString::GetStringData() const
{
	return m_pData;
}

// возвращает подстроку с заданной позиции длиной не больше length символов
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
