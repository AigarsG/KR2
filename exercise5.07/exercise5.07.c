#include <stdio.h>
#include "utils.h"
#include "exercise5.07.h"


int readlines(char *buf, size_t bufsz, char **lineptrs, size_t lineptrssz)
{
	int len, nlines;
	char *bufptr, line[80], *lineptr;

	nlines = 0;
	bufptr = buf;

	while ((len = mygetline(line, sizeof line / sizeof *line))
		&& nlines < lineptrssz) {
		lineptr = line;
		if (bufptr + len - buf < bufsz) {
			lineptrs[nlines++] = bufptr;
			while ((*bufptr = *lineptr)) 
				bufptr++, lineptr++;
			if (*(bufptr - 1) == '\n')
				*(bufptr - 1) = '\0';
		} 
	}

	return nlines;
}

