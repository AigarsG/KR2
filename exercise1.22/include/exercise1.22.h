#ifndef EXERCISE1_22_H_LOADED
#define EXERCISE1_22_H_LOADED

#define CHAR_PER_LINE 80


/*
 * Folds long input line in two or multiple lines breaking at last ecountered blank
 * or at CHAR_PER_LINEth character.
 * param   line: pointer to line to break
 * param    len: pointer to line length
 * param maxlen: maximum possible line length ( array size )
 */
void fold(char *line, int *len, int maxlen);

#endif
