#include <ctype.h>
#include "exercise5.06.h"


int patoi(char *s)
{
	int ret;
	
	ret = 0;

	while (*s) {
		if (isdigit(*s)) {
			ret = ret * 10 + (*s - '0');
			s++;	
		} else {
			return 0;
		}
	}

	return ret;
}


static char *rpitoa(int n, char *buf, enum BASE base, const int depth)
{
	int sign;
	int ibase = (int) base;

	sign = n < 0 ? -1 : 1;
	if (n / ibase)
		buf = rpitoa(n / ibase, buf, base, depth + 1);
	else {
		if (sign < 0)
			*buf++ = '-';
		if (base == OCTAL) {
			*buf++ = '0';
			*buf++ = 'o';
		} else if (base == HEXADECIMAL) {
			*buf++ = '0';
			*buf++ = 'x';
		}
	}

	if ((n * sign) % ibase > 9)
		*buf++ = '0' + (n * sign) % ibase + 39;
	else
		*buf++ = '0' + (n * sign) % ibase;

	if (depth == 0)
		*buf = '\0';

	return buf;	
}


char *pitoa(int n, char *buf, enum BASE base)
{
	char *ptr;

	ptr = buf;
	rpitoa(n, ptr, base, 0);

	return buf;
}


int pstrindex(const char *haystack, const char *needle)
{
	int ret;
	char *phaystack, *pneedle;

	ret = -1;
	pneedle = needle;
	phaystack = haystack;

	while (*phaystack) {
		pneedle = needle;
		while (1) {
			if (*pneedle != *(phaystack + (pneedle - needle))) {
				break;
			}
			pneedle++;
			if (!*pneedle) {
				ret = phaystack - haystack;
				break;
			}
		}
		phaystack++;
	}

	return ret;
}


void preverse(char *s)
{
	char *ptr, tmp;

	ptr = s;

	while (*(ptr + 1) && *(ptr + 1) != '\n')
		ptr++;

	while (s < ptr) {
		tmp = *s;
		*s = *ptr;
		*ptr = tmp;
		s++;
		ptr--;
	}

}
