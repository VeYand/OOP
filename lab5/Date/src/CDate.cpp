#include "../include/CDate.h"
#include <format>
#include <stdexcept>

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (year < EPOCH_YEAR)
	{
		throw std::underflow_error(
			std::format("Year must be greater than or equal to EPOCH_YEAR ({})", EPOCH_YEAR));
	}

	if (day > DaysInMonth(month, year))
	{
		throw std::overflow_error(
			std::format("Invalid day ({}) for month {} and year {}", day, static_cast<int>(month), year));
	}

	auto timestamp = CalculateDaysSinceEpoch(day, month, year);

	if (timestamp > MAX_TIMESTAMP)
	{
		throw std::overflow_error(
			std::format("Date {}-{}-{} exceeds maximum allowable timestamp", day, static_cast<int>(month), year));
	}

	m_timestamp = timestamp;
}

CDate::CDate(unsigned timestamp)
{
	if (timestamp > MAX_TIMESTAMP)
	{
		throw std::overflow_error(
			std::format("Timestamp {} exceeds maximum allowable timestamp", timestamp));
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
	while (days >= DAYS_IN_YEAR + IsLeapYear(year)) // todo без циклов
	{
		days -= DAYS_IN_YEAR + IsLeapYear(year);
		year++;
	}

	unsigned month = 1;
	while (days >= DaysInMonth(static_cast<Month>(month), year)) // todo без циклов
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
	while (days >= DAYS_IN_YEAR + IsLeapYear(year)) // todo без циклов
	{
		days -= DAYS_IN_YEAR + IsLeapYear(year);
		year++;
	}
	unsigned month = 1;
	while (days >= DaysInMonth(static_cast<Month>(month), year)) // todo без циклов
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
	while (days >= DAYS_IN_YEAR + IsLeapYear(year)) // todo без циклов
	{
		days -= DAYS_IN_YEAR + IsLeapYear(year);
		year++;
	}
	return year;
}

CDate::WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + static_cast<unsigned>(EPOCH_WEEK_DAY)) % DAYS_IN_WEEK);
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
	for (unsigned y = EPOCH_YEAR; y < year; ++y) // todo без циклов
		days += DAYS_IN_YEAR + IsLeapYear(y);

	for (unsigned m = 1; m < static_cast<unsigned>(month); ++m) // todo без циклов
		days += DaysInMonth(static_cast<Month>(m), year);

	return days;
}

CDate& CDate::operator++()
{
	if ((m_timestamp + 1) > MAX_TIMESTAMP)
	{
		throw std::overflow_error(
			std::format("Incrementing the date by one day would exceed the maximum allowable timestamp"));
	}

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
	if ((static_cast<int>(m_timestamp) - 1) < 0)
	{
		throw std::underflow_error("Decrementing the date by one day would result in a negative timestamp");
	}

	--m_timestamp;

	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp(*this);
	--(*this);
	return temp;
}

CDate operator+(const CDate& date, int days)
{
	return CDate(date.m_timestamp + days);
}

CDate operator+(int days, const CDate& date)
{
	return CDate(date.m_timestamp + days);
}

CDate operator-(const CDate& date, int days)
{
	if ((static_cast<int>(date.m_timestamp) - days) < 0)
	{
		throw std::underflow_error(
			std::format("Subtracting {} days would result in a negative timestamp", days));
	}

	return CDate(date.m_timestamp - days);
}

int operator-(const CDate& date1, const CDate& date2)
{
	auto deltaDays = static_cast<int>(date1.m_timestamp) - static_cast<int>(date2.m_timestamp);

	return deltaDays;
}

CDate& CDate::operator+=(int days)
{
	if ((m_timestamp + days) > MAX_TIMESTAMP)
	{
		throw std::overflow_error(
			std::format("Adding {} days would exceed the maximum allowable timestamp", days));
	}

	m_timestamp += days;

	return *this;
}

CDate& CDate::operator-=(int days)
{
	if (days > m_timestamp)
	{
		throw std::underflow_error("Subtraction result is negative.");
	}

	m_timestamp -= days;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	os << std::format("{}{}{}{}{}",
		date.GetDay(), CDate::DATE_DIVIDER,
		static_cast<int>(date.GetMonth()),
		CDate::DATE_DIVIDER,
		date.GetYear());

	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	unsigned day, month, year;
	char dot;

	if (!(is >> day >> dot >> month >> dot >> year))
	{
		is.setstate(std::ios_base::badbit);
		return is;
	}

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
