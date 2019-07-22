#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.09.h"
}


TEST_GROUP(group_1)
{
	int ret;
};


TEST(group_1, test_day_of_year)
{
	ret = day_of_year(2019, 4, 13);
	LONGS_EQUAL(103, ret);
}

TEST(group_1, test_day_of_year_leap_year)
{
	ret = day_of_year(2016, 4, 13);
	LONGS_EQUAL(104, ret);
}


TEST(group_1, test_day_of_year_invalid_day)
{
	ret = day_of_year(2016, 4, 32);
	LONGS_EQUAL(-1, ret);
	ret = day_of_year(2016, 4, 0);
	LONGS_EQUAL(-1, ret);
}

TEST(group_1, test_day_of_year_invalid_month)
{
	ret = day_of_year(2016, 13, 13);
	LONGS_EQUAL(-1, ret);
	ret = day_of_year(2016, 0, 13);
	LONGS_EQUAL(-1, ret);
}


TEST(group_1, test_day_of_year_invalid_year)
{
	ret = day_of_year(-1, 12, 12);
	LONGS_EQUAL(-1, ret);
}

TEST(group_1, test_month_day)
{
	int m, d;
	month_day(2019, 103, &m, &d);
	LONGS_EQUAL(4, m);
	LONGS_EQUAL(13, d);
}

TEST(group_1, test_month_day_leap_year)
{
	int m, d;
	month_day(1988, 60, &m, &d);
	LONGS_EQUAL(2, m);
	LONGS_EQUAL(29, d);
}

TEST(group_1, test_month_day_invalid_yearday)
{
	int m, d;
	m = 0;
	d = 0;
	ret = month_day(2019, 366, &m, &d);
	LONGS_EQUAL(-1, ret);
	LONGS_EQUAL(0, m);
	LONGS_EQUAL(0, d);
}

TEST(group_1, test_month_day_leap_year_invalid_yearday)
{
	int m, d;
	m = 0;
	d = 0;
	ret = month_day(1988, 0, &m, &d);
	LONGS_EQUAL(-1, ret);
	LONGS_EQUAL(0, m);
	LONGS_EQUAL(0, d);
	ret = month_day(1988, 367, &m, &d);
	LONGS_EQUAL(-1, ret);
	LONGS_EQUAL(0, m);
	LONGS_EQUAL(0, d);

}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

