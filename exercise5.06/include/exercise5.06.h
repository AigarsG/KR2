#ifndef EXERCISE5_06_HEADER
#define EXERCISE5_06_HEADER


enum BASE {
	OCTAL = 8,
	DECIMAL = 10,
	HEXADECIMAL = 16,
};


int patoi(char *s);
char *pitoa(int n, char *buf, enum BASE base);
int pstrindex(const char *haystack, const char *needle);
void preverse(char *s);

#endif
