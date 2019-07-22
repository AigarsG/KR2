#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise4.14.h"
}


TEST_GROUP(group_1)
{
};


TEST(group_1, test_swap_int)
{
	int a = 13;
	int b = -11;
	swap(int, a, b);

	LONGS_EQUAL(-11, a);
	LONGS_EQUAL(13, b);
}

TEST(group_1, test_swap_double)
{
	double a = -0.0031;
	double b = 1241.234;
	swap(double, a, b);

	DOUBLES_EQUAL(1241.234, a, 0);
	DOUBLES_EQUAL(-0.0031, b, 0);
}

TEST(group_1, test_concat_define)
{
	char * msg = concattok(MY, BASE);
	STRCMP_EQUAL("my base", msg);
}



int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

