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

	friend CDate operator+(const CDate& date, int days);
	friend CDate operator+(int days, const CDate& date);
	friend CDate operator-(const CDate& date, int days);
	friend int operator-(const CDate& date1, const CDate& date2);

	CDate& operator+=(int days);
	CDate& operator-=(int days);

	bool operator==(const CDate& CDate) const;
	bool operator!=(const CDate& date) const;

	bool operator<(const CDate& date) const;
	bool operator>(const CDate& date) const;

	bool operator<=(const CDate& date) const;
	bool operator>=(const CDate& date) const;

	friend std::ostream& operator<<(std::ostream& os, const CDate& date);
	friend std::istream& operator>>(std::istream& is, CDate& date);

private:
	constexpr static const unsigned MAX_TIMESTAMP = 2932896;
	constexpr static const unsigned DAYS_IN_YEAR = 365;
	constexpr static const unsigned EPOCH_YEAR = 1970;
	constexpr static const WeekDay EPOCH_WEEK_DAY = WeekDay::THURSDAY;
	constexpr static const unsigned DAYS_IN_WEEK = 7;
	constexpr static const char DATE_DIVIDER = '.';
	unsigned m_timestamp;
	static bool IsLeapYear(unsigned year);
	static unsigned DaysInMonth(Month month, unsigned year);
	static unsigned CalculateDaysSinceEpoch(unsigned day, Month month, unsigned year);
};

#endif // DATE_CDATE_H
