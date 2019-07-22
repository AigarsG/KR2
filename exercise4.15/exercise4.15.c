#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "exercise4.15.h"


int getint(char *s, int *retval)
{
	int c, sign;
	static char *currs = NULL;

	if (s)
		currs = s;

	if (currs) {
		while (isspace((c = *currs)))
			currs++;
		if (!isdigit(c) && c != EOF && c != '+' && c != '-')
			return 0;

		sign = (c == '-') ? -1 : 1;

		*retval = 0;
		if (c == '-' || c == '+')
			c = *++currs;
		if (!isdigit(c))
			return 0;
		if (c == EOF)
			return EOF;
		while (isdigit(c)) {
			*retval = *retval * 10 + (c - '0');
			c = *++currs;
		}
		*retval *= sign;

		return 1;
	}

	return EOF;
}

