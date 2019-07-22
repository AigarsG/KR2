#include <stdio.h>
#include <string.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"


#define MAXLINE 256


TEST_GROUP(group_1)
{
	FILE *fp;
	char *cmd;
	char buf[MAXLINE];

	void setup()
	{
		memset(buf, 0, sizeof buf / sizeof *buf);
	}

	void teardown()
	{
		pclose(fp);
	}
};

TEST(group_1, test_expr_simple)
{
	cmd = "../exercise5.10 12.3 -2.3 + +0.5 /";
	fp = popen(cmd, "r");
	CHECK(fp != NULL);
	CHECK(fgets(buf, sizeof buf / sizeof *buf, fp) != NULL);

	DOUBLES_EQUAL(20.0, atof(buf), 0.0);
}

TEST(group_1, test_expr_complex)
{
	cmd = "../exercise5.10 -3.16 16.76 -0.6 c= b= a= a b + c + 2 pow";
	fp = popen(cmd, "r");
	CHECK(fp != NULL);
	CHECK(fgets(buf, sizeof buf / sizeof *buf, fp) != NULL);

	DOUBLES_EQUAL(169.0, atof(buf), 0.0);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

