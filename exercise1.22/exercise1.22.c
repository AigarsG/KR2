#include <stdio.h>
#include "utils.h"
#include "exercise1.22.h"
#define DEBUG 0



void fold(char *line, int *len, int maxlen) {
    if (DEBUG) {
        printf("start of function fold('%.*s', %d, %d, %d)\n", *len - 1, line, *len, maxlen, CHAR_PER_LINE);
    }
    if (*len <= CHAR_PER_LINE || CHAR_PER_LINE < 1) {
        return;
    }

    int latest_blank_idx = -1;
    int inserted_nl_idx = 0;
    int i;
    for (i = 0; i < *len; i++) {
        if (line[i] == ' ') {
            if (DEBUG) {
                printf("' ' at %d\n", i);
            }
            latest_blank_idx = i;
        }
        if ((i - inserted_nl_idx) > 0 && (i - inserted_nl_idx) % CHAR_PER_LINE == 0) {
            if (DEBUG) {
                printf("Break point reached at i=%d, (last_nl_idx + 1)=%d and CHAR_PER_LINE=%d\n", i, inserted_nl_idx, CHAR_PER_LINE);
            }
            if (latest_blank_idx > -1) {
                /* break at last blank */
                line[latest_blank_idx] = '\n'; 
                inserted_nl_idx = latest_blank_idx + 1;
                latest_blank_idx = -1;
            } else {
                /* add hyphen and newline if enough space */
                if (*len + 1 <= maxlen) {
                    shift(line, len, i, 1);
                    line[i] = '\n';
                    inserted_nl_idx = i + 1;
                } else {
                    printf("Cannot make space for '-' and '\\n' characters, array is full\n");
                }
            }
        } 
    }
    if (DEBUG) {
        printf("end of function fold\n");
    }
}   


int main() {
    char line[MAXLINE];
    int len = mygetline(line, MAXLINE);
    fold(line, &len, MAXLINE);
    printf("%s", line);
    return 0;
}

