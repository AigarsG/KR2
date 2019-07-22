#include "exercise5.03.h"


static void point_to_end_of_str(char **s)
{
	while (**s)
		(*s)++;
}


static void append_str(char *s, char *t)
{
	while (*t)
		*s++ = *t++;
	*s = *t;
}


void pstrcat(char *s, char *t)
{
	point_to_end_of_str(&s);
	append_str(s, t);
}

