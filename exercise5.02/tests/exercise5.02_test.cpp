#include <stdio.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.02.h"
}


TEST_GROUP(group_1)
{
};


TEST(group_1, test_getfloat_1)
{
	int i, ret;
	char s[] = "-0.2345  245.3 -99.232 +.232 .000123";
	double nums[sizeof s / sizeof *s];

	i = 0;
	ret = getfloat(s, nums + i++);
	while (ret != EOF && ret) {
		ret = getfloat(NULL, nums + i++);
	}

	DOUBLES_EQUAL(-0.2345, nums[0], 0.000001);
	DOUBLES_EQUAL(245.3, nums[1], 0);
	DOUBLES_EQUAL(-99.232, nums[2], 0);
	DOUBLES_EQUAL(+.232, nums[3], 0);
	DOUBLES_EQUAL(0.000123, nums[4], 0);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

