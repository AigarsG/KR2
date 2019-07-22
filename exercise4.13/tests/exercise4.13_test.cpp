#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise4.13.h"
}


TEST_GROUP(group_1)
{
};


TEST(group_1, reverse_string_1)
{
	char string[] = "this is a string";
	rreverse(string, sizeof string / sizeof *string);
	STRCMP_EQUAL("gnirts a si siht", string);
}

TEST(group_1, reverse_string_odd_len)
{
	char string[] = "abolsg";
	rreverse(string, sizeof string / sizeof *string);
	STRCMP_EQUAL("gsloba", string);
}

TEST(group_1, reverse_string_even_len)
{
	char string[] = "abols";
	rreverse(string, sizeof string / sizeof *string);
	STRCMP_EQUAL("sloba", string);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
