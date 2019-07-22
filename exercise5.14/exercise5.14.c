#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <ctype.h>
#include <limits.h>
#include "utils.h"
#include "exercise5.14.h"

#define MAXLINES	5000
#define MAXLEN		1000
#define FIELD_MIN	0
#define FIELD_MAX	(sizeof(void *) * CHAR_BIT - 1)

enum argbit
{
	ARG_N = 0,
	ARG_R,
	ARG_F,
	ARG_D,
	ARG_CNT
};

static void swap(void *v[], int i, int j)
{
	void *tmp;
	tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

static int is_dord_chr(char c)
{
	return isalnum(c) || c == '\t' || c == ' ';
}

static void myqsort(void *v[], int left, int right, int (*comp)(void *, void *),
	int reverse)
{
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++) {
		if (reverse) {
			if ((*comp)(v[i], v[left]) > 0)
				swap(v, ++last, i);
		} else {
			if ((*comp)(v[i], v[left]) < 0)
				swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	myqsort(v, left, last - 1, comp, reverse);
	myqsort(v, last + 1, right, comp, reverse);
}

static int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	if (v1 > v2)
		return 1;
	return 0;
}

static int mystrcmp(char *s1, char *s2, int case_insensitive, int directory_order)
{
	char tmp1, tmp2;


	if (!s1 && !s2)
		return 0;
	if (!s1 && s2)
		return -1;
	if (s1 && !s2)
		return 1;


	while (*s1 && *s2) {
		if (directory_order) {
			if (!is_dord_chr(*s1)) {
				s1++;
				continue;
			}
			if (!is_dord_chr(*s2)) {
				s2++;
				continue;
			}
		}
		if (case_insensitive) {
			tmp1 = tolower(*s1);
			tmp2 = tolower(*s2);
		} else {
			tmp1 = *s1;
			tmp2 = *s2;
		}
		if (tmp1 < tmp2)
			return -1;
		if (tmp1 > tmp2)
			return 1;
		s1++;
		s2++;
	}
	return *s1 - *s2;
}

static int strcmp_case_insensitive(char *s1, char *s2)
{
	return mystrcmp(s1, s2, 1, 0);
}

static int strcmp_directory_order(char *s1, char *s2)
{
	return mystrcmp(s1, s2, 0, 1);
}

static int strcmp_directory_order_case_insensitive(char *s1, char *s2)
{
	return mystrcmp(s1, s2, 1, 1);
}

static int parse_args(int argc, char **argv, unsigned long *argmask)
{
	char c, *arg;

	while (*argv) {
		arg = *argv++;
		if (strlen(arg) < 2 || arg[0] != '-')
			continue;
		while ((c = *(++arg))) {
			switch (c) {
			case 'n':
				set_bit(ARG_N, argmask);
				break;
			case 'r':
				set_bit(ARG_R, argmask);
				break;
			case 'f':
				set_bit(ARG_F, argmask);
				break;
			case 'd':
				set_bit(ARG_D, argmask);
				break;
			default:
				fprintf(stderr, "%s: error: unknown option character '%c'\n",
					__FUNCTION__, c);
				return 1;
			}
		}
	}

	return 0;
}

static void print_result(char *lineptrs[])
{
	while (*lineptrs)
		printf("%s", *lineptrs++);
}

static int readlines(char *lineptr[], int nlines)
{
	int ret = 0;
	static char lines[MAXLINES][MAXLEN];
	static size_t maxlines = sizeof lines / sizeof *lines;
	static size_t maxlen = sizeof *lines / sizeof **lines;
	size_t curlen;
	char buff[maxlen + 1];

	if (nlines > maxlines) {
		fprintf(stderr,
			"%s: warning: nlines > maxlines,"
			" resetting nlines to maxlines\n", __FUNCTION__);
		nlines = maxlines;
	}

	/* Reset */
	memset(lines, 0, maxlines * maxlen);

	while (mygetline(buff, sizeof buff / sizeof *buff)) {
		if (ret >= nlines) {
			fprintf(stderr,
				"%s: error: maximum number of lines reached\n",
				__FUNCTION__);
			return -1;
		}
		curlen = strlen(buff) + 1;
		if (curlen > maxlen) {
			fprintf(stderr,
				"%s: error: maximum length for line reached\n",
				__FUNCTION__);
			return -1;
		}
		strcpy(lines[ret], buff);
		lineptr[ret] = lines[ret];
		ret++;
	}

	return ret;
}

static void remove_empty_lines(char *lineptrs[], size_t sz)
{
	size_t i, j;
	char *newptrs[sz];

	memset(newptrs, 0, sizeof newptrs);
	for (i = 0, j = 0; i < sz; i++) {
		if (!lineptrs[i])
			break;
		if (!(lineptrs[i][0] == '\n')) {
			newptrs[j++] = lineptrs[i];
		}
	}

	for (i = 0; i < j; i++) {
		lineptrs[i] = newptrs[i];
	}

	/* Set last line to NULL */
	if (i < sz)
		lineptrs[i] = NULL;
}

int main(int argc, char **argv)
{
	int ret;
	unsigned long argmask;
	char *lineptrs[MAXLINES + 1];
	size_t lineptrssz;

	memset(lineptrs, 0, sizeof lineptrs);
	lineptrssz = sizeof lineptrs / sizeof *lineptrs - 1;

	ret = readlines(lineptrs, lineptrssz);
	if (ret < 0) {
		fprintf(stderr, "error: input too big to sort\n");
		return 1;
	}

	argmask = 0;
	parse_args(argc, argv + 1, &argmask);

	if (get_bit(ARG_N, &argmask)) {
		myqsort((void **) lineptrs, 0, ret - 1,
			(int (*)(void *, void *)) numcmp,
			get_bit(ARG_R, &argmask));
	} else if (get_bit(ARG_F, &argmask) && get_bit(ARG_D, &argmask)) {
		myqsort((void **) lineptrs, 0, ret - 1,
			(int (*)(void *, void *)) strcmp_directory_order_case_insensitive,
			get_bit(ARG_R, &argmask));
	} else if (get_bit(ARG_F, &argmask)) {
		myqsort((void **) lineptrs, 0, ret - 1,
			(int (*)(void *, void *)) strcmp_case_insensitive,
			get_bit(ARG_R, &argmask));
	} else if (get_bit(ARG_D, &argmask)) {
		myqsort((void **) lineptrs, 0, ret - 1,
			(int (*)(void *, void *)) strcmp_directory_order,
			get_bit(ARG_R, &argmask));
	} else {
		myqsort((void **) lineptrs, 0, ret - 1,
			(int (*)(void *, void *)) strcmp,
			get_bit(ARG_R, &argmask));
	}

	remove_empty_lines(lineptrs, lineptrssz);
	print_result(lineptrs);
	return 0;
}
