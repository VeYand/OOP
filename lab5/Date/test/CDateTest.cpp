#include "../include/CDate.h"
#include <gtest/gtest.h>

TEST(CDateTest, DefaultConstructor)
{
	auto date = CDate();

	EXPECT_EQ(1, date.GetDay());
	EXPECT_EQ(CDate::Month::JANUARY, date.GetMonth());
	EXPECT_EQ(CDate::WeekDay::THURSDAY, date.GetWeekDay());
	EXPECT_EQ(1970, date.GetYear());
}

TEST(CDateTest, ZeroTimestampConstructor)
{
	auto date = CDate(0);

	EXPECT_EQ(1, date.GetDay());
	EXPECT_EQ(CDate::Month::JANUARY, date.GetMonth());
	EXPECT_EQ(CDate::WeekDay::THURSDAY, date.GetWeekDay());
	EXPECT_EQ(1970, date.GetYear());
}

TEST(CDateTest, NotZeroTimestampConstructor)
{
	auto date = CDate(19832);

	EXPECT_EQ(19, date.GetDay());
	EXPECT_EQ(CDate::Month::APRIL, date.GetMonth());
	EXPECT_EQ(CDate::WeekDay::FRIDAY, date.GetWeekDay());
	EXPECT_EQ(2024, date.GetYear());
}

TEST(CDateTest, DateConstructorValid)
{
	auto date = CDate(1, CDate::Month::APRIL, 2024);

	EXPECT_EQ(1, date.GetDay());
	EXPECT_EQ(CDate::Month::APRIL, date.GetMonth());
	EXPECT_EQ(CDate::WeekDay::MONDAY, date.GetWeekDay());
	EXPECT_EQ(2024, date.GetYear());
}

TEST(CDateTest, DateConstructorInvalidYear)
{
	EXPECT_THROW(CDate(31, CDate::Month::DECEMBER, 1969), std::underflow_error);
	EXPECT_NO_THROW(CDate(1, CDate::Month::JANUARY, 1970));

	EXPECT_THROW(CDate(1, CDate::Month::JANUARY, 10000), std::overflow_error);
	EXPECT_NO_THROW(CDate(31, CDate::Month::DECEMBER, 9999));

}

TEST(CDateTest, DateDayConstructor)
{
	EXPECT_THROW(CDate(30, CDate::Month::FEBRUARY, 1970), std::overflow_error);
	EXPECT_THROW(CDate(29, CDate::Month::FEBRUARY, 1970), std::overflow_error);
	EXPECT_NO_THROW(CDate(28, CDate::Month::FEBRUARY, 1970));

	EXPECT_THROW(CDate(30, CDate::Month::FEBRUARY, 1972), std::overflow_error);
	EXPECT_NO_THROW(CDate(29, CDate::Month::FEBRUARY, 1972));
	EXPECT_NO_THROW(CDate(28, CDate::Month::FEBRUARY, 1972));

	for (auto month : { CDate::Month::JANUARY, CDate::Month::MARCH, CDate::Month::MAY,
			 CDate::Month::JULY, CDate::Month::AUGUST, CDate::Month::OCTOBER, CDate::Month::DECEMBER })
	{
		EXPECT_THROW(CDate(32, month, 1970), std::overflow_error);
		EXPECT_NO_THROW(CDate(31, month, 1970));
		EXPECT_NO_THROW(CDate(30, month, 1970));

		EXPECT_THROW(CDate(32, month, 1972), std::overflow_error);
		EXPECT_NO_THROW(CDate(31, month, 1972));
		EXPECT_NO_THROW(CDate(30, month, 1972));
	}

	for (auto month : { CDate::Month::APRIL, CDate::Month::JUNE, CDate::Month::SEPTEMBER, CDate::Month::NOVEMBER })
	{
		EXPECT_THROW(CDate(32, month, 1970), std::overflow_error);
		EXPECT_THROW(CDate(31, month, 1970), std::overflow_error);
		EXPECT_NO_THROW(CDate(30, month, 1970));
		EXPECT_NO_THROW(CDate(29, month, 1970));

		EXPECT_THROW(CDate(31, month, 1972), std::overflow_error);
		EXPECT_NO_THROW(CDate(30, month, 1972));
		EXPECT_NO_THROW(CDate(29, month, 1972));
	}
}

TEST(CDateTest, IncrementDecrementOperators)
{
	CDate date(1, CDate::Month::JANUARY, 2024);
	++date;
	EXPECT_EQ(CDate(2, CDate::Month::JANUARY, 2024), date);

	date = CDate(1, CDate::Month::JANUARY, 2024);
	date++;
	EXPECT_EQ(CDate(2, CDate::Month::JANUARY, 2024), date);

	date = CDate(1, CDate::Month::JANUARY, 2024);
	--date;
	EXPECT_EQ(CDate(31, CDate::Month::DECEMBER, 2023), date);

	date = CDate(1, CDate::Month::JANUARY, 2024);
	date--;
	EXPECT_EQ(CDate(31, CDate::Month::DECEMBER, 2023), date);
}

TEST(CDateTest, AdditionSubtractionOperatorsWithNumber)
{
	CDate date(1, CDate::Month::JANUARY, 2024);
	date = date + 10;
	EXPECT_EQ(CDate(11, CDate::Month::JANUARY, 2024), date);

	date += 21;
	EXPECT_EQ(CDate(1, CDate::Month::FEBRUARY, 2024), date);

	date = date - 10;
	EXPECT_EQ(CDate(22, CDate::Month::JANUARY, 2024), date);

	date -= 22;
	EXPECT_EQ(CDate(31, CDate::Month::DECEMBER, 2023), date);
}

TEST(CDateTest, InvalidAdditionOperators)
{
	auto maxDate = CDate(31, CDate::Month::DECEMBER, 9999);

	EXPECT_THROW(++maxDate, std::overflow_error);
	EXPECT_THROW(maxDate++, std::overflow_error);
	EXPECT_THROW(maxDate + 1, std::overflow_error);
	EXPECT_THROW(maxDate += 1, std::overflow_error);
}

TEST(CDateTest, InvalidSubtractionOperators)
{
	auto date = CDate();

	EXPECT_THROW(--date, std::underflow_error);
	EXPECT_THROW(date--, std::underflow_error);
	EXPECT_THROW(date - 1, std::underflow_error);
	EXPECT_THROW(date -= 1, std::underflow_error);
}

TEST(CDateTest, SubtractionOperatorsWithDate)
{
	CDate date1(1, CDate::Month::JANUARY, 2024);
	CDate date2(10, CDate::Month::JANUARY, 2024);

	int difference = date2 - date1;
	EXPECT_EQ(9, difference);

	difference = date1 - date2;
	EXPECT_EQ(-9, difference);
}

TEST(CDateTest, ComparisonOperators)
{
	CDate date1(1, CDate::Month::JANUARY, 2024);
	CDate date2(10, CDate::Month::JANUARY, 2024);
	CDate date3(10, CDate::Month::JANUARY, 2024);

	EXPECT_TRUE(date1 < date2);
	EXPECT_FALSE(date1 > date2);
	EXPECT_TRUE(date2 == date3);
	EXPECT_FALSE(date1 == date2);
	EXPECT_TRUE(date1 <= date2);
	EXPECT_TRUE(date2 <= date3);
	EXPECT_TRUE(date2 >= date1);
	EXPECT_TRUE(date3 >= date2);
}

TEST(CDateTest, OutputOperator)
{
	CDate date(15, CDate::Month::FEBRUARY, 2023);
	std::ostringstream oss;
	oss << date;
	EXPECT_EQ("15.2.2023", oss.str());
}

TEST(CDateTest, InputOperator)
{
	std::istringstream iss("25.12.2022");
	CDate date;
	iss >> date;
	EXPECT_FALSE(iss.bad());
	EXPECT_EQ(25, date.GetDay());
	EXPECT_EQ(CDate::Month::DECEMBER, date.GetMonth());
	EXPECT_EQ(2022, date.GetYear());
}

TEST(CDateTest, InvalidInputDate)
{
	std::istringstream iss("25.2022");
	CDate date;
	iss >> date;
	EXPECT_TRUE(iss.bad());
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}