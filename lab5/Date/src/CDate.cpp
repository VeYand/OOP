#include "../include/CDate.h"
#include <format>
#include <stdexcept>

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (year < EPOCH_YEAR)
	{
		throw std::invalid_argument(std::format("Year must be greater than or equal to {}.", EPOCH_YEAR));
	}

	if (day > DaysInMonth(month, year))
	{
		throw std::invalid_argument("Invalid day for the given month.");
	}

	m_timestamp = CalculateDaysSinceEpoch(day, month, year);
}

CDate::CDate(unsigned timestamp)
{
	if (timestamp < 0)
	{
		throw std::invalid_argument("Timestamp cannot be negative.");
	}

	m_timestamp = timestamp;
}

CDate::CDate()
{
	m_timestamp = 0;
}

unsigned CDate::GetDay() const
{
	unsigned days = m_timestamp;

	unsigned year = EPOCH_YEAR;
	while (days >= DAYS_IN_YEAR + IsLeapYear(year))
	{
		days -= DAYS_IN_YEAR + IsLeapYear(year);
		year++;
	}

	unsigned month = 1;
	while (days >= DaysInMonth(static_cast<Month>(month), year))
	{
		days -= DaysInMonth(static_cast<Month>(month), year);
		month++;
	}

	return days + 1;
}

CDate::Month CDate::GetMonth() const
{
	unsigned days = m_timestamp;
	unsigned year = EPOCH_YEAR;
	while (days >= DAYS_IN_YEAR + IsLeapYear(year))
	{
		days -= DAYS_IN_YEAR + IsLeapYear(year);
		year++;
	}
	unsigned month = 1;
	while (days >= DaysInMonth(static_cast<Month>(month), year))
	{
		days -= DaysInMonth(static_cast<Month>(month), year);
		month++;
	}
	return static_cast<Month>(month);
}

unsigned CDate::GetYear() const
{
	unsigned days = m_timestamp;
	unsigned year = EPOCH_YEAR;
	while (days >= DAYS_IN_YEAR + IsLeapYear(year))
	{
		days -= DAYS_IN_YEAR + IsLeapYear(year);
		year++;
	}
	return year;
}

CDate::WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + 4) % DAYS_IN_WEEK);
}

bool CDate::IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned CDate::DaysInMonth(Month month, unsigned year)
{
	switch (month)
	{
	case Month::JANUARY:
	case Month::MARCH:
	case Month::MAY:
	case Month::JULY:
	case Month::AUGUST:
	case Month::OCTOBER:
	case Month::DECEMBER:
		return 31;
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	default:
		return 0;
	}
}

unsigned CDate::CalculateDaysSinceEpoch(unsigned day, Month month, unsigned year)
{
	unsigned days = day - 1;
	for (unsigned y = EPOCH_YEAR; y < year; ++y)
		days += DAYS_IN_YEAR + IsLeapYear(y);

	for (unsigned m = 1; m < static_cast<unsigned>(month); ++m)
		days += DaysInMonth(static_cast<Month>(m), year);

	return days;
}

CDate& CDate::operator++()
{
	++m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp(*this);
	++(*this);
	return temp;
}

CDate& CDate::operator--()
{
	--m_timestamp;

	if (m_timestamp < 0)
	{
		throw std::invalid_argument("Cannot decrement timestamp below zero.");
	}

	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp(*this);
	--(*this);
	return temp;
}

CDate CDate::operator+(int days) const
{
	return CDate(m_timestamp + days);
}

CDate CDate::operator-(int days) const
{
	if (days > m_timestamp)
	{
		throw std::invalid_argument("Subtraction result is negative.");
	}

	return CDate(m_timestamp - days);
}

int CDate::operator-(const CDate& date2) const
{
	auto deltaDays = static_cast<int>(m_timestamp) - static_cast<int>(date2.m_timestamp);

	return deltaDays;
}

CDate& CDate::operator+=(int days)
{
	m_timestamp += days;

	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (days > m_timestamp)
	{
		throw std::invalid_argument("Subtraction result is negative.");
	}

	m_timestamp -= days;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	os << date.GetDay() << "." << static_cast<int>(date.GetMonth()) << "." << date.GetYear();
	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned day, year;
	int month;
	char dot;
	is >> day >> dot >> month >> dot >> year;
	date = CDate(day, static_cast<CDate::Month>(month), year);
	return is;
}

bool CDate::operator==(const CDate& date) const
{
	return m_timestamp == date.m_timestamp;
}


bool CDate::operator!=(const CDate& date) const
{
	return m_timestamp != date.m_timestamp;
}

bool CDate::operator<(const CDate& date) const
{
	return m_timestamp < date.m_timestamp;
}

bool CDate::operator>(const CDate& date) const
{
	return m_timestamp > date.m_timestamp;
}

bool CDate::operator<=(const CDate& date) const
{
	return m_timestamp <= date.m_timestamp;
}

bool CDate::operator>=(const CDate& date) const
{
	return m_timestamp >= date.m_timestamp;
}
