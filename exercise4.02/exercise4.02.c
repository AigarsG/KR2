#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "exercise4.02.h"


double eatof(const char *s)
{
	double val, power;
	int i, sign, snsign, e;

	/* Skip white space */
	for (i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	/* Check for scientific notation */
	e = 0;
	if (tolower(s[i]) == 'e')
		i++;
	snsign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (isdigit(s[i])) {
		e *= 10;
		e += s[i] - '0';
		i++;
	}
	while (e > 0) {
		if (snsign > 0)
			power /= 10.0;
		else
			power *= 10.0;
		e--;
	}

	return sign * val / power;
}

