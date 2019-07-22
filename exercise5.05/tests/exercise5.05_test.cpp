#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.05.h"
}


TEST_GROUP(group_1)
{
	char s[100];
	char *ret;
};


TEST(group_1, test_mstrncpy_1)
{
	ret = mstrncpy(s, "this is a string", 8);
	STRCMP_EQUAL("this is ", ret);
	STRCMP_EQUAL("this is ", s);
}

TEST(group_1, test_mstrncpy_2)
{
	ret = mstrncpy(s, "this is a string", 16);
	STRCMP_EQUAL("this is a string", ret);
	STRCMP_EQUAL("this is a string", s);
}

TEST(group_1, test_mstrncat_3)
{
	s[0] = 'a';
	s[1] = 'b';
	s[2] = 'o';

	ret = mstrncat(s, "ls ir", 4);
	STRCMP_EQUAL("abols i", s);
	STRCMP_EQUAL("abols i", ret);
}

TEST(group_1, test_mstrncat_4)
{
	s[0] = 'a';
	s[1] = 'b';
	s[2] = 'o';

	ret = mstrncat(s, "ls ir labakais", 15);
	STRCMP_EQUAL("abols ir labakais", s);
	STRCMP_EQUAL("abols ir labakais", ret);
}

TEST(group_1, test_mstrncmp_positive_5)
{
	int equal;
	equal = mstrncmp("abols", "abols ", 5);
	LONGS_EQUAL(0, equal);
}

TEST(group_1, test_mstrncmp_negative_6)
{
	int equal;
	equal = mstrncmp("abols", "abols ", 6);
	LONGS_EQUAL(-1, equal);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

