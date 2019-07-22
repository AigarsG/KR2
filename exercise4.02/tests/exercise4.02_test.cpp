#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise4.02.h"
}


TEST_GROUP(group_1)
{
	double ret;
};


TEST(group_1, test_str_to_double_1)
{
	const char *s = "13.1441";
	double expected = 13.1441;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}


TEST(group_1, test_str_to_double_2)
{
	const char *s = "-8.11";
	double expected = -8.11;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

TEST(group_1, test_str_to_double_3)
{
	const char *s = "+6.00";
	double expected = 6.0;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

TEST(group_1, test_str_to_double_4)
{
	const char *s = "25";
	double expected = 25;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

TEST(group_1, test_str_to_double_5)
{
	const char *s = "-375.3199e+4";
	double expected = -3753199;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

TEST(group_1, test_str_to_double_6)
{
	const char *s = "60e-3";
	double expected = 0.06;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

TEST(group_1, test_str_to_double_7)
{
	const char *s = "19.611E0";
	double expected = 19.611;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

TEST(group_1, test_str_to_double_8)
{
	const char *s = "333333333E-11";
	double expected = 0.00333333333;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

TEST(group_1, test_str_to_double_9)
{
	const char *s = "0.0000000198931e13";
	double expected = 198931;
	ret = eatof(s);
	DOUBLES_EQUAL(expected, ret, 0.0);
}

int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}