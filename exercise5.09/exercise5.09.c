#include <stdio.h>
#include "utils.h"
#include "exercise5.09.h"


static const int daytab[2][13] =
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


static int is_leap_year(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0 ? 1 : 0;
}


int day_of_year(int year, int month, int day)
{
	int i, leap;

	if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
		return -1;

	leap = is_leap_year(year);

	for (i = 1; i < month; i++)
		day += *(*(daytab + leap) + i);

	return day;
}


int month_day(int year, int yearday, int *retmonth, int *retday)
{
	int i, leap;

	if (year < 0 || yearday < 1 || yearday > 366)
		return -1;

	leap = is_leap_year(year);
	if (!leap && yearday > 365)
		return -1;

	for (i = 1; yearday > *(*(daytab + leap) + i); i++)
		yearday -= *(*(daytab + leap) + i);

	*retmonth = i;
	*retday = yearday;

	return 0;
}