#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

extern "C" {
#include "exercise5.11.h"
}


TEST_GROUP(group_1)
{
	int fd1[2], fd2[2];
	pid_t pid;
	char *line;

	void setup()
	{

		if (pipe(fd1)) {
			perror("pipe");
			exit(-1);
		}

		if (pipe(fd2)) {
			perror("pipe");
			exit(-1);
		}

		pid = fork();

		switch (pid) {
		case -1:
			perror("fork");
			exit(-1);
		case 0:
			/* close writing end of first pipe */
			close(fd1[1]);
			/* close reading end of second pipe */
			close(fd2[0]);
			/* connect reading end of first pipe to stdin */
			dup2(fd1[0], STDIN_FILENO);
			/* connect writing end of second pipe to stdout */
			dup2(fd2[1], STDOUT_FILENO);
			/* close reading end of first pipe*/
			close(fd1[0]);
			/* close writing end of second pipe*/
			close(fd2[1]);
			break;
		default:
			/* close reading end of first pipe */
			close(fd1[0]);
			/* close writing end of second pipe */
			close(fd2[1]);
			break;
		}
	}

	void teardown()
	{
	}
};

TEST(group_1, test_entab_1)
{
	line = "This is        a sample                string       "
		"with  a lot of spaces";
	char result[strlen(line) + 1];
	switch (pid) {
	case -1:
		perror("fork");
		exit(-1);
	case 0:
		execl("../exercise5.11", "exercise5.11", "entab", "-0", "+8",
			NULL);
		break;
	default:
		/* write to writing end of first pipe */
		write(fd1[1], line, strlen(line) + 1);
		/* close writing end of first pipe */
		close(fd1[1]);
		/* wait for child output */
		wait(NULL);
		/* read childs output */
		read(fd2[0], result, sizeof result / sizeof *result);
		/* close writing end of first pipe */
		close(fd1[1]);

		STRCMP_EQUAL("This is\ta sample\t\tstring       "
		"with  a lot of spaces", result);

		break;
	} 
}

TEST(group_1, test_entab_2)
{
	line = "This is      a sample          string     with a lot of spaces";
	char result[strlen(line) + 1];
	switch (pid) {
	case -1:
		perror("fork");
		exit(-1);
	case 0:
		execl("../exercise5.11", "exercise5.11", "entab", "-2", "+4",
			NULL);
		break;
	default:
		/* write to writing end of first pipe */
		write(fd1[1], line, strlen(line) + 1);
		/* close writing end of first pipe */
		close(fd1[1]);
		/* wait for child output */
		wait(NULL);
		/* read childs output */
		read(fd2[0], result, sizeof result / sizeof *result);
		/* close writing end of first pipe */
		close(fd1[1]);

		STRCMP_EQUAL("This is  \ta sample  \t\tstring     "
				"with a lot of spaces", result);

		break;
	} 
}

TEST(group_1, test_detab_3)
{
	line = "This is\t a sample \tstring \t with\t\ta lot of tabs";
	char result[strlen(line) + 5 * 8 + 1];
	switch (pid) {
	case -1:
		perror("fork");
		exit(-1);
	case 0:
		execl("../exercise5.11", "exercise5.11", "detab", "-0", "+8",
			NULL);
		break;
	default:
		/* write to writing end of first pipe */
		write(fd1[1], line, strlen(line) + 1);
		/* close writing end of first pipe */
		close(fd1[1]);
		/* wait for child output */
		wait(NULL);
		/* read childs output */
		read(fd2[0], result, sizeof result / sizeof *result);
		/* close writing end of first pipe */
		close(fd1[1]);

		STRCMP_EQUAL("This is         a sample         string          "
			"with                a lot of tabs", result);

		break;
	} 
}

TEST(group_1, test_detab_4)
{
	line = "This is\t a sample \tstring \t with\t\ta lot of tabs";
	char result[strlen(line) + 1 * 4 + 1];
	switch (pid) {
	case -1:
		perror("fork");
		exit(-1);
	case 0:
		execl("../exercise5.11", "exercise5.11", "detab", "-1", "+4",
			NULL);
		break;
	default:
		/* write to writing end of first pipe */
		write(fd1[1], line, strlen(line) + 1);
		/* close writing end of first pipe */
		close(fd1[1]);
		/* wait for child output */
		wait(NULL);
		/* read childs output */
		read(fd2[0], result, sizeof result / sizeof *result);
		/* close writing end of first pipe */
		close(fd1[1]);

		STRCMP_EQUAL("This is\t a sample \tstring \t with\t    "
			"a lot of tabs", result);

		break;
	} 
}


int main(int argc, char** argv)
{
	return CommandLineTestRunner::RunAllTests(argc, argv);
}
