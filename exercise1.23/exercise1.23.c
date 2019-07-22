#include <stdio.h>
#include "utils.h"
#include "exercise1.22.h"
#include "exercise1.23.h"

/* 
 *  '=39
 *  "=34
 *\ /=47
 *\ *=42
 */


/* 
 * Remove comments from input line.
 * Handle quoted strings properly (hint: do not remove comment within it)
 */


void remove_comments(char *line, int *len) {
    char buffer[*len];
    char quote = 0;
    char cur_ch, next_ch;
    int i;
    int j = 0;
    int max = *len;
    short in_comment = 0;
    
    for (i = 0; i < max - 1; i++) {
        cur_ch = line[i];
        next_ch = line[i + 1];


        /* TODO rewrite this with variable ignore_char */

        /* Determine if character should be ignored ( in comment ) */
        switch (cur_ch) {
            /* " or ' */
            case 34: case 39:
                if (quote) {
                    buffer[j++] = cur_ch;
                    if (i == max-2) {
                        buffer[j++] = next_ch;
                    }
                    /* End of quoted text */
                    if (cur_ch == quote) {
                        quote = 0;
                    }
                } else {
                    if (!in_comment) {
                        buffer[j++] = cur_ch;
                        if (i == max-2) {
                            buffer[j++] = next_ch;
                        }
                        /* Start of quoted text */
                        quote = cur_ch;
                    }
                }
                break;
            /*\ * */ 
            case 42:
                if (!quote) {
                    if (!in_comment) {
                        buffer[j++] = cur_ch;
                        if (i == max-2) {
                            buffer[j++] = next_ch;
                        }

                    } else {
                        if (next_ch == '/') {
                            i++;
                            in_comment = 0;
                        }
                    }
                } else {
                    buffer[j++] = cur_ch;
                    if (i == max-2) {
                        buffer[j++] = next_ch;
                    }
                }
                break;
            /*\ / */
            case 47:
                if (!quote) {
                    if (!in_comment) {
                        if (next_ch == '*') {
                            in_comment = 1;
                        } else {
                            buffer[j++] = cur_ch;
                            if (i == max-2) {
                                buffer[j++] = next_ch;
                            }
                        }
                    }
                } else {
                    buffer[j++] = cur_ch;
                    if (i == max-2) {
                        buffer[j++] = next_ch;
                    }
                }
                break;
            default:
                if (!in_comment) {
                    buffer[j++] = cur_ch;
                    if (i == max-2) {
                        buffer[j++] = next_ch;
                    }
                }
                break;
        }
    }

    for (i = 0; i < *len; i++) {
        if (i < j) {
            line[i] = buffer[i];
        } else {
            line[i] = '\0';
        }
    }
    *len = j;
}



int main() {
    /* TODO rewrite to use only getchar */
    char line[MAXLINE];
    int len = mygetline(line, MAXLINE);
    fold(line, &len, MAXLINE);*/
    remove_comments(line, &len);
    printf("%s", line);
    return 0;
}

