#include <stdio.h>
#include "utils.h"
#include "exercise5.04.h"


static char * get_end_of_str(char *s)
{
	while (*s)
		s++;
	return --s;
}


int strend(char *s, char *t)
{
	char *send, *tend;

	send = get_end_of_str(s);
	tend = get_end_of_str(t);

	while (*send-- == *tend--) {
		if (send < s)
			break;
		if (tend < t)
			return 1;
	}

	return 0;
}

