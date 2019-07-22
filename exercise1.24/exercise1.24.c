#include <stdio.h>
#include "utils.h"
#include "exercise1.24.h"


/* PS. the design of this program is shit, too many globals, but I am still learning :) */


short in_comment = 0;
short esc = 0;
char quote = '\0';
int nline = 0;
int open_curly_brackets = 0;
int open_brackets = 0;



int check_for_errors(char* line, int sz) {
    int i;
    char ch;
    if (sz > 0) {
        nline++;
        for (i = 0; i < sz - 1; i++) {
            /* write checks for enclosed comments, ', ", {, *\/ ( characters and correct escape sequences */
            ch = line[i];
            if (ch == '\\') {
                if (!esc) {
                    esc = 1;
                } else {
                    esc = 0;
                }
            } else if (ch == '/') {
                if (line[i+1] == '*' && quote == '\0') {
                    if (!in_comment) {
                        in_comment = 1;
                        i++;
                    } else {
                        /* asteric should be escaped */
                        printf("Error on line %d at index %d, unescaped '%c'\n", nline, i, ch);
                        return 1;
                    }
                }
            } else if (ch == '*') {
                /* Comments do not care about esc before asterik so no checks */
                if (line[i+1] == '/' && quote == '\0') {
                    in_comment = 0;    
                    i++;
                }
            } else if (ch == '\"' || ch == '\'') {
                /* Handle quotes */
                if (!in_comment) {
                    if (quote == '\0') {
                        quote = ch;
                    } else if (quote == ch) {
                        if (!esc) {
                            quote = '\0';
                        } else {
                            esc = 0;
                        }
                    }
                }
            } else if (ch == '(') {
                if (!in_comment && quote == '\0') {
                    open_brackets++;
                }
            } else if (ch == ')') {
                if (!in_comment && quote == '\0') {
                    open_brackets--;
                }
            } else if (ch == '{') {
                if (!in_comment && quote == '\0') {
                    open_curly_brackets++;
                }
            } else if (ch == '}') {
                if (!in_comment && quote == '\0') {
                    open_curly_brackets--;
                }
            } else if (ch == 'n' || ch == 't' || ch == 'b' || ch == 'r') {
                if (esc) {
                    esc = 0;
                }
            } else {
                if (esc) {
                    printf("Error on line %d at index %d, expected escape character, instead got '%c'\n", nline, i, ch);
                    return 1;
                }
            }
        }
    } else {
        /* Print all errors */
        if (in_comment) {
            printf("Error, unable to locate end of comment\n");
        } else if (quote != '\0') {
            printf("Error, unable to locate end quote '%c'\n", quote);
        } else if (open_brackets > 0) {
            if (open_brackets > 1) {
                printf("Error, unable to locate %d closing brackets ')'\n", open_brackets);
            } else {
                printf("Error, unable to locate closing bracket ')'\n");
            }
        } else if (open_brackets < 0) {
            if (open_brackets < -1) {
                printf("Error, unable to locate %d opening brackets '('\n", open_brackets);
            } else {
                printf("Error, unable to locate opening bracket '('\n");
            }
 
        } else if (open_curly_brackets > 0) {
            if (open_curly_brackets > 1) {
                printf("Error, unable to locate %d closing curly brackets '}'\n", open_curly_brackets);
            } else {
                printf("Error, unable to locate closing curly bracket '}'\n");
            }
        } else if (open_curly_brackets < 0) {
            if (open_curly_brackets < -1) {
                printf("Error, unable to locate %d opening curly brackets '{'\n", open_curly_brackets);
            } else {
                printf("Error, unable to locate opening curly bracket '{'\n");
            }
 
        }  

    }
    return 0;
}




int main() {
    char line[MAXLINE];
    int len;
    int i;
    for (i = 0; i < MAXLINES; i++) {
        len = mygetline(line, MAXLINE);
        if (check_for_errors(line, len)) {
            break;
        } else if (len == 0) {
            break;
        }
    }
    return 0;
}

