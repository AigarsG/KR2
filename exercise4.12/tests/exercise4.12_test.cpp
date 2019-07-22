#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise4.12.h"
}


TEST_GROUP(ritoa_tests)
{
	char string[100];
	size_t bufsz;
	size_t idx;
	int ret;

	void setup()
	{
		bufsz = sizeof string / sizeof * string;
		idx = 0;
	}
};


TEST(ritoa_tests, test_max_positive)
{
	ret = ritoa(2147483647, string, bufsz, &idx);
	LONGS_EQUAL(0, ret);
	STRCMP_EQUAL("2147483647", string);
}

TEST(ritoa_tests, test_zero)
{
	ret = ritoa(0000, string, bufsz, &idx);
	LONGS_EQUAL(0, ret);
	STRCMP_EQUAL("0", string);
}


TEST(ritoa_tests, test_min_negative)
{
	ret = ritoa(-2147483648, string, bufsz, &idx);
	LONGS_EQUAL(0, ret);
	STRCMP_EQUAL("-2147483648", string);
}

int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

