#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise6.02.h"
}

static const long PAGE_SIZE = sysconf(_SC_PAGESIZE);
static const long NLINES = 1024;


TEST_GROUP(exercise6_02)
{
	const char *input, *outfile;
	char *lines[NLINES];
	int ret;
	FILE *fp;

	int getlines(char **linebuffer, size_t size, FILE *stream)
	{
		size_t n;
		int i;
		i = 0;
		fseek(stream, 0, SEEK_SET);
		while (i < size && getline(&linebuffer[i], &n, stream) > 0)
			i++;
		return i;
	}

	void setup()
	{
		input = NULL;
		outfile = "output.txt";
		fp = fopen(outfile, "w+");
	}

	void teardown()
	{
		int i;
		fclose(fp);
		for (i = 0; i < sizeof lines / sizeof *lines; i++) {
			if (lines[i])
				free(lines[i]);
		}
	}
};

TEST(exercise6_02, print_unique_variables_01)
{
	int i;
	const char *expected[] = {"coord: 2\n","strin: 3\n"};
	input = "char *string;\n"
		"size_t string_len;\n"
		"/*size_t string_sz;*/\n"
		"int coordx, coordy, coordz;";
	print_unique_variables(input, fp, 5);
	ret = getlines(lines, sizeof lines / sizeof *lines, fp);

	CHECK_EQUAL(sizeof expected / sizeof *expected, ret);
	for (i = 0; i < sizeof expected / sizeof *expected; i++)
		STRCMP_EQUAL(expected[i], lines[i]);
}

TEST(exercise6_02, print_unique_variables_02)
{
	int i;
	const char *expected[] = {"coordx: 1\n,","coordy: 1\n","coordz: 1\n",
		"string: 3\n"};
	input = "char *string;\n"
		"size_t string_len;\n"
		"/*size_t string_sz;*/\n"
		"int coordx, coordy, coordz;";
	print_unique_variables(input, fp, 6);
	ret = getlines(lines, sizeof lines / sizeof *lines, fp);

	CHECK_EQUAL(sizeof expected / sizeof *expected, ret);
	for (i = 0; i < sizeof expected / sizeof *expected; i++)
		STRCMP_EQUAL(expected[i], lines[i]);
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
