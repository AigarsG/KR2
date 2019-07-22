#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.04.h"
}


TEST_GROUP(group_1)
{
	int ret;
};


TEST(group_1, test_strend_positive_1)
{
	ret = strend("abols ir LaBais", "aBais");
	LONGS_EQUAL(1, ret);
}

TEST(group_1, test_strend_negative_2)
{
	ret = strend("abols ir LaBais", "abais");
	LONGS_EQUAL(0, ret);
}

TEST(group_1, test_strend_negative_3)
{
	ret = strend("abols", "kas tas par shit");
	LONGS_EQUAL(0, ret);
}



int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

