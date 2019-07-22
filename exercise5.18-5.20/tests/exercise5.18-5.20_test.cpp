#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "exercise5.18-5.20.h"
}

#define MAX_LEN 1024


TEST_GROUP(decl2text)
{
	struct keyval {
		const char *decl;
		const char *expr;
	};
	char buf[MAX_LEN];

	void setup()
	{
		memset(buf, 0, sizeof buf);
	}
};

TEST(decl2text, decl2text_01_standard_input)
{
	struct keyval decls[] = {
		{"int *ptr", "ptr: pointer to int"},
		{"char s[10]", "s: array[10] of char"},
		{"short (*ptr)", "ptr: pointer to short"},
		{"int (*daytab)[13]", "daytab: pointer to array[13] of int"},
		{"int *daytab[12]", "daytab: array[12] of pointer to int"},
		{"char **argv", "argv: pointer to pointer to char"},
		{"void *comp()", "comp: function returning pointer to void"},
		{"void (*comp)()", "comp: pointer to function returning void"},
		{"char (*(*x())[])()", "x: function returning pointer to"
			" array[] of pointer to function returning char"},
		{"char (*(*x[3])())[5]", "x: array[3] of pointer to function "
			"returning pointer to array[5] of char"}
	};

	int i;
	for (i = 0; i < sizeof decls / sizeof *decls; i++) {
		memset(buf, 0, sizeof buf / sizeof *buf);
		CHECK_EQUAL(0, decl2text(decls[i].decl, buf, sizeof buf / sizeof *buf));
		STRCMP_EQUAL(decls[i].expr, buf);
	}
}
#if 0
TEST(decl2text, decl2text_02_non_standard_input)
{
	struct keyval decls[] = {
		{"char   *  *argv", "argv: pointer to pointer to char"},
		{"const char **argv", "argv: pointer to pointer to const char"}
	};

	int i;
	for (i = 0; i < sizeof decls / sizeof *decls; i++) {
		memset(buf, 0, sizeof buf / sizeof *buf);
		CHECK_EQUAL(0, decl2text(decls[i].decl, buf, sizeof buf / sizeof *buf));
		STRCMP_EQUAL(decls[i].expr, buf);
	}
}
#endif
int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
