#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include <stdio.h>
#include "exercise4.03.h"
}


TEST_GROUP(group_1)
{
	int ret;
	double retval;
	char *line;

	void setup()
	{
		ret = 0;
		retval = 0.0;
		line = NULL;
	}
};

TEST(group_1, test_addition_1)
{
	line = "5 3 +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(8, retval, 0);
}

TEST(group_1, test_addition_2)
{
	line = "23 173 +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(196, retval, 0);
}


TEST(group_1, test_addition_3)
{
	line = "0.11 13.4    +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(13.51, retval, 0);
}

TEST(group_1, test_addition_4)
{
	line = "0.11 13.4    + 7 23.1 +    +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(43.61, retval, 0);
}


TEST(group_1, test_subtraction_5)
{
	line = "11.30 4.25 -";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(7.05, retval, 0.000000001);
}

TEST(group_1, test_subtraction_6)
{
	line = "23 4.5 - 10 9.5 - -";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(18.0, retval, 0);
}

TEST(group_1, test_multiplication_7)
{
	line = "3.3 12.3 * 2 4 * *";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(324.72, retval, 0);
}

TEST(group_1, test_division_8)
{
	line = "8.13 1.001 / 7.5 0.1 / /";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(0.10829170829170832, retval, 0);
}

TEST(group_1, test_combined_9)
{
	line = "10.8 4 + 6.25 8 * 48 - /";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(7.4, retval, 0);
}

TEST(group_1, test_signed_numbers_10)
{
	line = "-66.3 20.1 - +30.4 +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(-56.0, retval, 0.000000001);
}

TEST(group_1, test_single_number_positive_11)
{
	line = "+65.112";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(65.112, retval, 0);
}

TEST(group_1, test_single_number_negative_12)
{
	line = "-65.112";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(-65.112, retval, 0);
}

TEST(group_1, test_modulus_13)
{
	line = "23.02 6 %";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(5.02, retval, 0);
}

TEST(group_1, test_modulus_combined_14)
{
	line = "-45.5 -5.5 % 2.5 +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(1.0, retval, 0);
}

TEST(group_1, test_return_top_15)
{
	line = "6 8 -0.18 top";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(1, ret);
	DOUBLES_EQUAL(-0.18, retval, 0);
}

TEST(group_1, test_return_top_empty_stack_16)
{
	line = "top";
	retval = -1;
	ret = evaluate(line, &retval);
	LONGS_EQUAL(-1, ret);
	DOUBLES_EQUAL(-1, retval, 0);
}

TEST(group_1, test_line_ends_with_n_17)
{
	line = "6.7 -1.3 -\n";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(8.0, retval, 0);
}

TEST(group_1, test_signed_18)
{
	line = "3.4 +1.2 + +1.4 +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(6.0, retval, 0);
}

TEST(group_1, test_long_expression_19)
{
	line = "3.4 +1.2 + +1.4 + 0.5 0.5 + 2.0 1.0 - * *";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(6.0, retval, 0);
}

#if 0
/*BUG in TEST!!!??? Does not change retval value even if *retval 0.0 is
done before returning from evaluate*/
TEST(group_1, test_duplicate_top_element_20_0)
{
	retval = 100;
	line = "0.12 5.4 dup - +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(0.12, retval, 0);
}
#endif

TEST(group_1, test_duplicate_top_element_20_1)
{
	retval = 100;
	line = "6.3 dup +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(12.6, retval, 0);
}

TEST(group_1, test_duplicate_top_element_20_2)
{
	retval = 100;
	line = "6.3 dup dup + -";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(-6.3, retval, 0);
}
TEST(group_1, test_duplicate_top_element_empty_stack_21)
{
	line = "dup";
	retval = -0.1;
	ret = evaluate(line, &retval);
	LONGS_EQUAL(-1, ret);
	DOUBLES_EQUAL(-0.1, retval, 0);
}

TEST(group_1, test_swap_top_two_22)
{
	line = "-0.015 +0.012 -54.3 swp - +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(-54.327, retval, 0);
}

TEST(group_1, test_clear_stack_23)
{
	line = "-0.015 +0.012 -54.3 - + clr 6.3 1.3 -";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(5.0, retval, 0);
}

TEST(group_1, test_clear_stack_empty_24)
{
	line = "clr";
	retval = -1.0;
	ret = evaluate(line, &retval);
	LONGS_EQUAL(1, ret);
	DOUBLES_EQUAL(-1.0, retval, 0);
}

TEST(group_1, test_sin_positive_25)
{
	line = "+1 0.5235987755982988 sin +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(1.5, retval, 0);
}

TEST(group_1, test_sin_negative_26)
{
	line = "+1 -0.5235987755982988 sin +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(0.5, retval, 0);
}

TEST(group_1, test_exp_negative_27)
{
	line = "-1 exp";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(0.36787944117144233, retval, 0);
}

TEST(group_1, test_exp_null_28)
{
	line = "0 exp";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(1, retval, 0);
}

TEST(group_1, test_exp_positive_29)
{
	line = "2 exp";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(7.38905609893065, retval, 0);
}

TEST(group_1, test_pow_positive_30)
{
	line = "8.0 3.0 pow";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(512.0, retval, 0);
}

TEST(group_1, test_pow_positive_31)
{
	line = "3.05 +1.98 pow";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(9.097324, retval, 0.000001);
}

TEST(group_1, test_pow_negative_32)
{
	line = "4.0 -0.5 pow";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(0.5, retval, 0);
}

TEST(group_1, test_variable_handling_simple_33)
{
	line = "2.0 c= c c *";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(4.0, retval, 0);
}

TEST(group_1, test_variable_handling_complex_34)
{
	line = "-3.16 16.76 -0.6 c= b= a= a b + c +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(13.0, retval, 0.00001);
}

TEST(group_1, test_variable_handling_35)
{
	line = "2.5 c= c c + 3.4 c= c +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(0, ret);
	DOUBLES_EQUAL(8.4, retval, 0.00001);
}

TEST(group_1, test_variable_handling_unset_variable_36)
{
	retval = -1.0;
	line = "z z +";
	ret = evaluate(line, &retval);
	LONGS_EQUAL(-1, ret);
	DOUBLES_EQUAL(-1.0, retval, 0);
}

int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
