#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.07.h"
}


TEST_GROUP(group_1)
{
	int fd;

	void setup()
	{
		close(STDIN_FILENO);
		fd = open("./fixture.txt", O_RDONLY);
		if (fd < 0) {
			fprintf(stderr, "failed to open ./fixture.txt\n");
			exit(1);
		}
	}

	void teardown()
	{
		close(fd);
	}
};


TEST(group_1, test_readlines_1)
{
	char lines[10000];
	char *lineptr[50];
	int ret;
	ret = readlines(lines, sizeof lines / sizeof *lines, lineptr,
		sizeof lineptr / sizeof *lineptr);
	LONGS_EQUAL(3, ret);
	STRCMP_EQUAL("This is sample line nr1", lineptr[0]);
	STRCMP_EQUAL("This is another line", lineptr[1]);
	STRCMP_EQUAL("Orange is the best, whatever, son!", lineptr[2]);

}


TEST(group_1, test_readlines_2)
{
	char lines[50];
	char *lineptr[3];
	int ret;
	ret = readlines(lines, sizeof lines / sizeof *lines, lineptr,
		sizeof lineptr / sizeof *lineptr);
	LONGS_EQUAL(2, ret);
	STRCMP_EQUAL("This is sample line nr1", lineptr[0]);
	STRCMP_EQUAL("This is another line", lineptr[1]);

}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}

