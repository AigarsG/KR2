#include "exercise5.05.h"


char * mstrncpy(char *s, char *t, size_t n)
{
	char *ret;
	size_t count;

	ret = s;
	count = 0;
	while ((*s++ = *t++) && ++count < n);

	return ret;
}


char * mstrncat(char *s, char *t, size_t n)
{
	char *ret;
	size_t count;

	ret = s;
	count = 0;
	while (*s)
		s++;
	while ((*s = *t) && ++count < n)
		s++, t++;
	*s = *t;

	return ret;
}


int mstrncmp(char *s, char *t, size_t n)
{
	size_t count;

	count = 0;
	while (*t && count < n) {
		if (!*s || *s++ != *t++)
			return -1;
		count++;
	}

	return 0;
}