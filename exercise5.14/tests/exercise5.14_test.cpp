#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "utils.h"
}


TEST_GROUP(sort_tests)
{
	const char *cmd;
	FILE *fp;

	void teardown() {
		pclose(fp);
	}
};

TEST(sort_tests, test_1)
{
	cmd = "printf %s 'potato\noranges are awesome\napples are too\n\n"
		"onions...\n' | ../exercise5.14";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("apples are too\nonions...\noranges are awesome\npotato\n",
		ret);
}

TEST(sort_tests, test_2)
{
	cmd = "printf %s '4722\n13\n12.8\n-1.2\n-1.21\n\n' | ../exercise5.14 -n";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("-1.21\n-1.2\n12.8\n13\n4722\n", ret);
}

TEST(sort_tests, test_3)
{
	cmd = "printf %s 'oranges are awesome\npotato\napples are too\n\n"
		"onions...\n' | ../exercise5.14 -r";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("potato\noranges are awesome\nonions...\napples are too\n",
		ret);
}

TEST(sort_tests, test_4)
{
	cmd = "printf %s '4722\n13\n12.8\n-1.2\n-1.21\n\n' | ../exercise5.14 -n -r";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("4722\n13\n12.8\n-1.2\n-1.21\n", ret);
}

TEST(sort_tests, test_5)
{
	cmd = "printf %s 'Potato\noranges are awesome\napples are too\n\n"
		"Onions...\n' | ../exercise5.14 -f";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("apples are too\nOnions...\noranges are awesome\nPotato\n",
		ret);
}

TEST(sort_tests, test_6)
{
	cmd = "printf %s 'Potato\noranges are awesome\napples are too\n\n"
		"Onions...\n' | ../exercise5.14 -f -r";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("Potato\noranges are awesome\nOnions...\napples are too\n",
		ret);
}

TEST(sort_tests, test_7)
{
	cmd = "printf %s '!potato\n..oranges are awesome\napples are too\n\n"
		"Onions...\n' | ../exercise5.14 -d";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("Onions...\napples are too\n..oranges are awesome\n!potato\n",
		ret);
}

TEST(sort_tests, test_8)
{
	cmd = "printf %s '!potato\n..oranges are awesome\napples are too\n\n"
		"Onions...\n' | ../exercise5.14 -d -f";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("apples are too\nOnions...\n..oranges are awesome\n!potato\n",
		ret);
}

TEST(sort_tests, test_9)
{
	cmd = "printf %s '!potato\n..oranges are awesome\napples are too\n\n"
		"Onions...\n' | ../exercise5.14 -df";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("apples are too\nOnions...\n..oranges are awesome\n!potato\n",
		ret);
}

TEST(sort_tests, test_10)
{
	cmd = "printf %s '!potato\n..oranges are awesome\napples are too\n\n"
		"Onions...\n' | ../exercise5.14 -d f";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("Onions...\napples are too\n..oranges are awesome\n!potato\n",
		ret);
}

#if 0
TEST(sort_tests, test_11)
{
	cmd = "printf %s '5412 Black orange\n413 white apple\n512 blue sky\n"
		"413 green apple\n'"" | ../exercise5.14 -0-d f";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("413 green apple\n413 white apple\n512 blue sky\n"
		"5412 Black orange\n", ret);
}

TEST(sort_tests, test_12)
{
	cmd = "printf %s '5412 Black orange\n413 white apple\n512 blue sky\n'"
		" | ../exercise5.14 -1df";

	fp = popen(cmd, "r");
	CHECK(fp != NULL);

	char ret[strlen(cmd) + 1];
	mlfgets(ret, sizeof ret, fp);
	STRCMP_EQUAL("5412 Black orange\n512 blue sky\n413 white apple\n",
		ret);
}
#endif

int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
