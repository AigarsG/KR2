#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "exercise4.13.h"


void rreverse(char *s, size_t len)
{
	char tmp, *ptr;
	long idx;

	ptr = s;
	idx = strlen(s) - (len - strlen(s));

	if (idx > 1)
		rreverse(++ptr, len);

	tmp = s[0];
	s[0] = s[idx];
	s[idx] = tmp;
}