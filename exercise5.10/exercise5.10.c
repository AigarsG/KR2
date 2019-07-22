#include <stdio.h>
#include <string.h>
#include "exercise5.10.h"
#include "exercise4.03.h"


static int strconcat(char **strings, size_t sz, char *retbuf, size_t retsz)
{
	int i;
	size_t strsz, totsz;

	totsz = 0;
	for (i = 0; i < sz; i++) {
		strsz = strlen(strings[i]);
		if (totsz + strsz <= retsz) {
			strcat(retbuf, " ");
			strcat(retbuf, strings[i]);
		} else {
			fprintf(stderr, "%s: error: not enough space in buffer\n",
				__FUNCTION__);
			return -1;
		}
		totsz += strsz;
	}

	return 0;
}


int main(int argc, char **argv)
{
	char buf[256];
	char *cmdargs[argc-1];
	int i, ret;
	double result;

	memset(buf, 0, sizeof buf);

	for (i = 0; i < sizeof cmdargs / sizeof *cmdargs; i++)
		cmdargs[i] = argv[i + 1];

	ret = strconcat(cmdargs, sizeof cmdargs / sizeof *cmdargs, buf,
		sizeof buf / sizeof *buf);

	if (ret < 0)
		return ret;

	ret = evaluate(buf, &result);

	if (!ret)
		printf("%f", result);

	return ret;
}