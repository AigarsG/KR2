#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exercise5.11.h"
#include "utils.h"


static size_t entab(char *s, size_t sz, unsigned int col0, unsigned int nspaces);
static size_t detab(char *s, size_t sz, unsigned int col0, unsigned int nspaces);
static void print_usage(void);


static void print_usage(void)
{
	printf("usage: ./binary detab|entab [-m][+n]\n");
}

static int has_n_conseq_spaces(char *s, size_t sz, int n)
{
	size_t i;
	int c;

	for (i = 0, c = 0; i < sz && s[i] == ' '; i++) {
		if (++c == n) {
			return 1;
		}
	}
	return 0;
}

static size_t entab(char *s, size_t sz, unsigned int col0, unsigned int nspaces)
{
	size_t i, j;
	char buf[sz];
	int ignored_spaces;

	if (sz < nspaces || col0 > nspaces)
		return sz;

	memset(buf, 0, sz);

	for (i = 0, j = 0, ignored_spaces = 0; i < sz;) {
		if (s[i] == ' ') {
			if (ignored_spaces++ >= col0) {
				if (has_n_conseq_spaces(s+i, sz - i, nspaces)) {
					buf[j++] = '\t';
					i += nspaces;
				} else {
					buf[j++] = s[i++];
				}
			} else {
				buf[j++] = s[i++];
			}
		} else {
			buf[j++] = s[i++];
			ignored_spaces = 0;
		}
	}
	memcpy(s, buf, sz);

	return j;
}


static size_t detab(char *s, size_t sz, unsigned int col0, unsigned int nspaces)
{
	size_t i, j, k;
	char buf[sz];
	int ignored_tabs;

	if (sz < nspaces || col0 > nspaces)
		return sz;

	memset(buf, 0, sz);

	for (i = 0, j = 0, ignored_tabs = 0; i < sz && j < sz; i++) {
		if (s[i] == '\t') {
			if (ignored_tabs++ >= col0) {
				k = j + nspaces;
				while (j < k && j < sz) {
					buf[j++] = ' ';
				}
			} else {
				buf[j++] = s[i];	
			}
		} else if (s[i] == '\0') {
			buf[j] = s[i];
			break;
		} else {
			buf[j++] = s[i];
			ignored_tabs = 0;
		}
	}

	if (j == sz)
		return sz;

	memcpy(s, buf, sz);

	return j;
}


int main(int argc, char **argv)
{
	int col0;
	int nspaces;
	int i;
	size_t max;

	char line[256], *cmd;

	col0 = -1;
	nspaces = -1;

	if (argc < 2) {
		print_usage();
		return -1;		
	}

	if (!strncmp("detab", argv[1], 6)) {
		cmd = "detab";
	} else if (!strncmp("entab", argv[1], 6)) {
		cmd = "entab";
	} else {
		fprintf(stderr, "error: unknown command\n");
		print_usage();
		return -1;
	}

	if (argc == 2) {
		col0 = 0;
		nspaces = 4;
	} else {
		/* TODO */
		for (i = 2; i < argc; i++) {
			max = strlen(argv[i]);
			char subbuf[max];
			if (argv[i][0] == '-' && col0 == -1) {
				if (max < 2) {
					fprintf(stderr,
						"error: unknown argument %s\n",
						argv[i]);
					continue;
				}
				memcpy(subbuf, &argv[i][1], max);
				col0 = strtol(subbuf, NULL, 10);
			} else if (argv[i][0] == '+' && nspaces == -1) {
				if (max < 2) {
					fprintf(stderr,
						"error: unknown argument %s\n",
						argv[i]);
					continue;
				}
				memcpy(subbuf, &argv[i][1], max);
				nspaces = strtol(subbuf, NULL, 10);
			}
		}
	}

	if (col0 == -1)
		col0 = 0;
	if (nspaces == -1)
		nspaces = 4;

	mygetline(line, sizeof line / sizeof *line);

	if (!strcmp("detab", cmd)) {
		detab(line, sizeof line, col0, nspaces);	
	} else {
		entab(line, sizeof line, col0, nspaces);
	}

	printf("%s", line);

	return 0;
}