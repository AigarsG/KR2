#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.03.h"
}


TEST_GROUP(group_1)
{
	int ret;
};


TEST(group_1, test_strcat_1)
{
	char s[30] = "this is a";
	pstrcat(s, " string");
	STRCMP_EQUAL("this is a string", s);
}

TEST(group_1, test_strcat_2)
{
	char s[50] = "I am an amazi";
	pstrcat(s, "ng programmer and lover");
	STRCMP_EQUAL("I am an amazing programmer and lover", s);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

