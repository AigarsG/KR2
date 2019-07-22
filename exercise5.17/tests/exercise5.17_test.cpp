#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.17.h"
}


TEST_GROUP(exercise5_17)
{
	const char *lines[6];

	void setup()
	{
		lines[0] = "wet Oranges\n";
		lines[1] = "";
		lines[2] = "awesome potatoes are here\n";
		lines[3] = "Awesome fruits as well\n";
		lines[4] = "\n";
		lines[5] = "this is awesome\n";
	}
};

TEST(exercise5_17, fieldsort_wo_fields_wo_flags_01)
{
	fieldsort(lines, sizeof lines / sizeof *lines, NULL);
	STRCMP_EQUAL("", lines[0]);
	STRCMP_EQUAL("\n", lines[1]);
	STRCMP_EQUAL("Awesome fruits as well\n", lines[2]);
	STRCMP_EQUAL("awesome potatoes are here\n", lines[3]);
	STRCMP_EQUAL("this is awesome\n", lines[4]);
	STRCMP_EQUAL("wet Oranges\n", lines[5]);
}

TEST(exercise5_17, fieldsort_wo_fields_wo_flags_02)
{
	fieldsort(lines, sizeof lines / sizeof *lines, "");
	STRCMP_EQUAL("", lines[0]);
	STRCMP_EQUAL("\n", lines[1]);
	STRCMP_EQUAL("Awesome fruits as well\n", lines[2]);
	STRCMP_EQUAL("awesome potatoes are here\n", lines[3]);
	STRCMP_EQUAL("this is awesome\n", lines[4]);
	STRCMP_EQUAL("wet Oranges\n", lines[5]);
}

TEST(exercise5_17, fieldsort_wo_fields_wo_flags_03)
{
	lines[0] = "+218\n";
	lines[1] = ".11\n";
	lines[2] = ".0\n";
	lines[3] = "-0.13\n";
	lines[4] = "-.14\n";
	lines[5] = "13\n";

	fieldsort(lines, sizeof lines / sizeof *lines, "");
	STRCMP_EQUAL("+218\n", lines[0]);
	STRCMP_EQUAL("-.14\n", lines[1]);
	STRCMP_EQUAL("-0.13\n", lines[2]);
	STRCMP_EQUAL(".0\n", lines[3]);
	STRCMP_EQUAL(".11\n", lines[4]);
	STRCMP_EQUAL("13\n", lines[5]);
}

TEST(exercise5_17, fieldsort_wo_fields_w_flags_01)
{
	lines[0] = "+218\n";
	lines[1] = ".11\n";
	lines[2] = ".0\n";
	lines[3] = "-0.13\n";
	lines[4] = "-.14\n";
	lines[5] = "13\n";

	fieldsort(lines, sizeof lines / sizeof *lines, "-n");
	STRCMP_EQUAL("-.14\n", lines[0]);
	STRCMP_EQUAL("-0.13\n", lines[1]);
	STRCMP_EQUAL(".0\n", lines[2]);
	STRCMP_EQUAL(".11\n", lines[3]);
	STRCMP_EQUAL("13\n", lines[4]);
	STRCMP_EQUAL("+218\n", lines[5]);
}

TEST(exercise5_17, fieldsort_wo_fields_w_flags_02)
{
	lines[0] = "+218\n";
	lines[1] = ".11\n";
	lines[2] = ".0\n";
	lines[3] = "-0.13\n";
	lines[4] = "-.14\n";
	lines[5] = "13\n";

	fieldsort(lines, sizeof lines / sizeof *lines, "-n-r");
	STRCMP_EQUAL("+218\n", lines[0]);
	STRCMP_EQUAL("13\n", lines[1]);
	STRCMP_EQUAL(".11\n", lines[2]);
	STRCMP_EQUAL(".0\n", lines[3]);
	STRCMP_EQUAL("-0.13\n", lines[4]);
	STRCMP_EQUAL("-.14\n", lines[5]);
}

TEST(exercise5_17, fieldsort_w_fields_w_flags_01)
{
	fieldsort(lines, sizeof lines / sizeof *lines, "-1");

	STRCMP_EQUAL("wet Oranges\n", lines[0]);
	STRCMP_EQUAL("Awesome fruits as well\n", lines[1]);
	STRCMP_EQUAL("this is awesome\n", lines[2]);
	STRCMP_EQUAL("awesome potatoes are here\n", lines[3]);
	STRCMP_EQUAL("\n", lines[4]);
	STRCMP_EQUAL("", lines[5]);
}

TEST(exercise5_17, fieldsort_w_fields_w_flags_02)
{
	lines[0] = "apples +218\n";
	lines[1] = "Raisins .11\n";
	lines[2] = "Bananas .12\n";
	lines[3] = "Orange 14\n";
	lines[4] = "Cucumber .13\n";
	lines[5] = "salt 13\n";

	fieldsort(lines, sizeof lines / sizeof *lines, "-1n");
	STRCMP_EQUAL("Raisins .11\n", lines[0]);
	STRCMP_EQUAL("Bananas .12\n", lines[1]);
	STRCMP_EQUAL("Cucumber .13\n", lines[2]);
	STRCMP_EQUAL("salt 13\n", lines[3]);
	STRCMP_EQUAL("Orange 14\n", lines[4]);
	STRCMP_EQUAL("apples +218\n", lines[5]);
}

TEST_GROUP(exercise5_17_multiple_fields)
{
	const char *lines[6];

	void setup()
	{
		lines[0] = "manners maketh 5 man\n";
		lines[1] = "manners maketh 4 man\n";
		lines[2] = "manners Maketh 3 man\n";
		lines[3] = "maketh manners 5 man\n";
		lines[4] = "maketh manners 4 man\n";
		lines[5] = "maketh Manners 3 man\n";
	}
};

TEST(exercise5_17_multiple_fields, fieldsort_w_fields_w_flags_01)
{
	lines[0] = "apples +218 yada\n";
	lines[1] = "Raisins .11 Whatever\n";
	lines[2] = "Bananas .11 blah\n";
	lines[3] = "Orange 14 bar\n";
	lines[4] = "Cucumber .11 foo\n";
	lines[5] = "salt 13 apples\n";

	fieldsort(lines, sizeof lines / sizeof *lines, "-1n -0");
	STRCMP_EQUAL("Bananas .11 blah\n", lines[0]);
	STRCMP_EQUAL("Cucumber .11 foo\n", lines[1]);
	STRCMP_EQUAL("Raisins .11 Whatever\n", lines[2]);
	STRCMP_EQUAL("salt 13 apples\n", lines[3]);
	STRCMP_EQUAL("Orange 14 bar\n", lines[4]);
	STRCMP_EQUAL("apples +218 yada\n", lines[5]);
}

TEST(exercise5_17_multiple_fields, fieldsort_w_fields_w_flags_02)
{
	fieldsort(lines, sizeof lines / sizeof *lines, "-1r -2n");
	STRCMP_EQUAL("maketh manners 4 man\n", lines[0]);
	STRCMP_EQUAL("maketh manners 5 man\n", lines[1]);
	STRCMP_EQUAL("manners maketh 4 man\n", lines[2]);
	STRCMP_EQUAL("manners maketh 5 man\n", lines[3]);
	STRCMP_EQUAL("maketh Manners 3 man\n", lines[4]);
	STRCMP_EQUAL("manners Maketh 3 man\n", lines[5]);
}

TEST(exercise5_17_multiple_fields, fieldsort_w_fields_w_flags_03)
{
	fieldsort(lines, sizeof lines / sizeof *lines, "-1rf -2nr");
	STRCMP_EQUAL("maketh manners 5 man\n", lines[0]);
	STRCMP_EQUAL("maketh manners 4 man\n", lines[1]);
	STRCMP_EQUAL("maketh Manners 3 man\n", lines[2]);
	STRCMP_EQUAL("manners maketh 5 man\n", lines[3]);
	STRCMP_EQUAL("manners maketh 4 man\n", lines[4]);
	STRCMP_EQUAL("manners Maketh 3 man\n", lines[5]);
}

TEST(exercise5_17_multiple_fields, fieldsort_w_fields_w_flags_04)
{
	lines[0] = "manners maketh 5 man\n";
	lines[1] = "manners maketh 4 man\n";
	lines[2] = "manners Maketh 3 man\n";
	lines[3] = "maketh manners 5 man\n";
	lines[4] = "maketh manners 4 man\n";
	lines[5] = "maketh Manners 3 man\n";

	lines[0] = ".manners maketh 5 man\n";
	lines[1] = ",manners maketh 4 man\n";
	fieldsort(lines, sizeof lines / sizeof *lines, "-0f");
	STRCMP_EQUAL(",manners maketh 4 man\n", lines[0]);
	STRCMP_EQUAL(".manners maketh 5 man\n", lines[1]);

	fieldsort(lines, sizeof lines / sizeof *lines, "-0fd");
	STRCMP_EQUAL("maketh manners 5 man\n", lines[0]);
	STRCMP_EQUAL("maketh Manners 3 man\n", lines[1]);
}

int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
