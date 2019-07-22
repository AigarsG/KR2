#include <stdio.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise4.15.h"
}


TEST_GROUP(group_1)
{
};


TEST(group_1, test_getint)
{
	char s[] = "-12 31 0";
	int ret, i, arry[sizeof s / sizeof *s];

	i = 0;
	ret = getint(s, &arry[i++]);
	while (ret != EOF && ret) {
		ret = getint(NULL, &arry[i++]);		
	}

	LONGS_EQUAL(-12, arry[0]);
	LONGS_EQUAL(31, arry[1]);
	LONGS_EQUAL(0, arry[2]);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

