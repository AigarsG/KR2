#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "utils.h"
}


TEST_GROUP(group_1)
{
	const char *cmd;
	FILE *fp;

	void teardown() {
		pclose(fp);
	}
};

TEST(group_1, 1_test_tail)
{
	cmd = "printf %s 'yada\nblaha blaha\nhey\n\nkahah' | ../exercise5.13 -n 3";
	fp = popen(cmd, "r");

	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);

	STRCMP_EQUAL("hey\n\nkahah", ret);
}

TEST(group_1, 2_test_tail)
{
	cmd = "printf %s 'yada\nblaha blaha\nhey\nc\nb' | ../exercise5.13";
	fp = popen(cmd, "r");

	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);

	STRCMP_EQUAL("yada\nblaha blaha\nhey\nc\nb", ret);
}

TEST(group_1, 3_test_tail_empty_string)
{
	cmd = "printf %s '' | ../exercise5.13";
	fp = popen(cmd, "r");

	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	memset(ret, 0, sizeof ret);
	fgets(ret, sizeof ret, fp);

	STRCMP_EQUAL("", ret);
}

TEST(group_1, 4_test_tail_empty_lines)
{
	cmd = "printf %s 'foo\n\nbar\n\n\n' | ../exercise5.13 -n 4";
	fp = popen(cmd, "r");

	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);

	STRCMP_EQUAL("\nbar\n\n\n", ret);
}

TEST(group_1, 5_test_tail_max_lines)
{
	char expected[297];
	char ret[sizeof expected];

	/* Expected 2\n3\n..101\n */
	cmd = "python -c 'for i in range(2, 102): print i'";
	fp = popen(cmd, "r");
	CHECK(fp != NULL);
	mlfgets(expected, sizeof expected, fp);
	pclose(fp);

	cmd = "python -c 'for i in range(1, 102): print i' | ../exercise5.13 -n 101";
	fp = popen(cmd, "r");
	CHECK(fp != NULL);
	mlfgets(ret, sizeof ret, fp);

	CHECK(strcmp("", expected));
	STRCMP_EQUAL(expected, ret);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
