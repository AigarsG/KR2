#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.06.h"
}


TEST_GROUP(group_1)
{
};


TEST(group_1, test_patoi_positive_1)
{
	int ret;

	ret = patoi("142045649");
	LONGS_EQUAL(142045649, ret);
}

TEST(group_1, test_patoi_negative_2)
{
	int ret;
	ret = patoi("this is not 124 a number");
	LONGS_EQUAL(0, ret);
}

TEST(group_1, test_patoi_negative_3)
{
	int ret;
	ret = patoi("124 a number");
	LONGS_EQUAL(0, ret);
}

TEST(group_1, test_pitoa_positive_decimal_4)
{
	char ret[50];
	pitoa(12410902, ret, DECIMAL);
	STRCMP_EQUAL("12410902", ret);
}

TEST(group_1, test_pitoa_negative_decimal_5)
{
	char ret[50];
	pitoa(-23512, ret, DECIMAL);
	STRCMP_EQUAL("-23512", ret);
}

TEST(group_1, test_pitoa_positive_octal_6)
{
	char ret[50];
	pitoa(+34593, ret, OCTAL);
	STRCMP_EQUAL("0o103441", ret);
}

TEST(group_1, test_pitoa_negative_octal_7)
{
	char ret[50];
	pitoa(-1241, ret, OCTAL);
	STRCMP_EQUAL("-0o2331", ret);
}

TEST(group_1, test_pitoa_positive_hexadecimal_8)
{
	char ret[50];
	pitoa(120098, ret, HEXADECIMAL);
	STRCMP_EQUAL("0x1d522", ret);
}

TEST(group_1, test_pitoa_negative_hexadecimal_9)
{
	char ret[50];
	pitoa(-123991, ret, HEXADECIMAL);
	STRCMP_EQUAL("-0x1e457", ret);
}

TEST(group_1, test_pstrindex_positive_10)
{
	int idx;

	idx = pstrindex("abols ir Super", "ir Super");
	LONGS_EQUAL(6, idx);
}

TEST(group_1, test_pstrindex_negative_11)
{
	int idx;

	idx = pstrindex("abols ir Super", "Ir Super");
	LONGS_EQUAL(-1, idx);
}

TEST(group_1, test_pstrindex_negative_12)
{
	int idx;

	idx = pstrindex("abols ir Super", "");
	LONGS_EQUAL(-1, idx);
}

TEST(group_1, test_preverse_13)
{
	char s[] = "abols ir Super";
	preverse(s);
	STRCMP_EQUAL("repuS ri sloba", s);
}

TEST(group_1, test_preverse_14)
{
	char s[] = "abols\n";
	preverse(s);
	STRCMP_EQUAL("sloba\n", s);
}

int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

