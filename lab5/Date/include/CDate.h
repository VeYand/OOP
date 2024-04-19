#ifndef DATE_CDATE_H
#define DATE_CDATE_H

#include <iostream>

class CDate
{
public:
	enum class Month
	{
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	enum class WeekDay
	{
		SUNDAY = 0,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY
	};

	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(unsigned timestamp);
	CDate();
	[[nodiscard]] unsigned GetDay() const;
	[[nodiscard]] Month GetMonth() const;
	[[nodiscard]] unsigned GetYear() const;
	[[nodiscard]] WeekDay GetWeekDay() const;

	CDate& operator++();
	CDate operator++(int);
	CDate& operator--();
	CDate operator--(int);
	CDate operator+(int days) const;
	CDate operator-(int days) const;
	int operator-(const CDate& date2) const;
	CDate& operator+=(int days);
	CDate& operator-=(int days);

	bool operator==(const CDate& CDate) const;
	bool operator!=(const CDate& date) const;

	bool operator<(const CDate& date) const;
	bool operator>(const CDate& date) const;

	bool operator<=(const CDate& date) const;
	bool operator>=(const CDate& date) const;

private:
	constexpr static const unsigned DAYS_IN_YEAR = 365;
	constexpr static const unsigned EPOCH_YEAR = 1970;
	constexpr static const unsigned DAYS_IN_WEEK = 7;
	unsigned m_timestamp;
	static bool IsLeapYear(unsigned year) ;
	static unsigned DaysInMonth(Month month, unsigned year) ;
	static unsigned CalculateDaysSinceEpoch(unsigned day, Month month, unsigned year);
};

std::ostream& operator<<(std::ostream& os, const CDate& date);
std::istream& operator>>(std::istream& is, CDate& date);

#endif // DATE_CDATE_H
