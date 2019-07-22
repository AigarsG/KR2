#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"
#include "exercise5.02.h"


int getfloat(char *s, double *retval)
{
	static char *currs = NULL;
	char c;
	int sign, fracdigit;

	if (s)
		currs = s;

	if (currs) {
		while (isspace((c = *currs)))
			currs++;
		if (!isdigit(c) && c != EOF && c != '-' && c != '+' && c != '.')
			return 0;
		sign = c == '-' ? -1 : 1;
		if (c == '-' || c == '+')
			c = *++currs;
		if (!isdigit(c) && c != '.')
			return 0;

		fracdigit = 0;
		*retval = 0.0;
		while (isdigit(c) || c == '.' && !fracdigit) {
			if (c == '.')
				fracdigit = 1;
			else if (fracdigit)
				*retval += (c - '0') / pow(10.0, fracdigit++);
			else
				*retval = *retval * 10.0 + (c - '0');
			c = *++currs;
		}
		*retval *= sign;

		return 1;
	}

	return EOF;
}

