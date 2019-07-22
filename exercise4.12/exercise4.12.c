#include <stdio.h>
#include "utils.h"
#include "exercise4.12.h"


int ritoa(int n, char *buf, size_t bufsz, size_t *idx)
{
	int ret, sign;

	sign = n;
	if (n < 0) {
		buf[(*idx)++] = '-';
		n = -(n + 1);
	}

	ret = 0;
	if (n / 10) {
		ret = ritoa(n / 10, buf, bufsz, idx);
	}

	if (ret)
		return ret;

	if (sign < 0)
		buf[(*idx)++] = '0' + n % 10 + 1;
	else
		buf[(*idx)++] = '0' + n % 10;

	return 0;
}
