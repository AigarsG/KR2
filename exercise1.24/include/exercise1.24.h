#ifndef EXERCISE1_24_H_INCLUDED
#define EXERCISE1_24_H_INCLUDED

#define MAXLINES 100

/*
 * Checks C source code for unbalanced parentheses, brackets, braces, quotes, comments, escape
 * sequences.
 */
int check_for_errors(char* line, int sz); 
extern short in_comment;
extern short esc;
extern char quote;
extern int nline;
extern int open_curly_brackets;
extern int open_brackets;

#endif
