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
	return GetCalendarDays().day;
}

CDate::Month CDate::GetMonth() const
{
	return GetCalendarDays().month;
}

unsigned CDate::GetYear() const
{
	return GetCalendarDays().year;
}

CDate::WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + static_cast<unsigned>(EPOCH_WEEK_DAY)) % DAYS_IN_WEEK);
}

bool CDate::IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

CDate::DateInfo CDate::GetCalendarDays() const
{
	unsigned year = (EPOCH_YEAR + 4 * m_timestamp / (DAYS_IN_YEAR * 4 + 1)) + 1;

	int daysGap = static_cast<int>(m_timestamp - CalculateDaysSinceEpoch(1, Month::JANUARY, year) + 1);
	if (daysGap <= 0)
	{
		year--;
		daysGap += static_cast<int>(DAYS_IN_YEAR) + IsLeapYear(year);
	}

	int monthIndex;
	unsigned d{};

	for (monthIndex = 0; monthIndex < 12 && daysGap > MONTHS_OFFSET[IsLeapYear(year)][monthIndex]; monthIndex++)
	{
		d = daysGap - MONTHS_OFFSET[IsLeapYear(year)][monthIndex];
	}

	return { d, static_cast<Month>(monthIndex), year };
}

unsigned CDate::CalculateDaysSinceEpoch(unsigned day, Month month, unsigned year)
{
	unsigned yearGap = year - EPOCH_YEAR;
	unsigned daysInYearGap = yearGap * DAYS_IN_YEAR + yearGap / 4 - yearGap / 100 + yearGap / 400;

	if (IsLeapYear(year - 1))
	{
		daysInYearGap++;
	}

	return daysInYearGap + MONTHS_OFFSET[IsLeapYear(year)][static_cast<unsigned>(month) - 1] + (day - 1);
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
