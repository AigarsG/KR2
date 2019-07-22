#include <stdio.h>
#include "utils.h"
#define MAXLINE 200
#define TAB_IN_SPACES 4



void entab(char*, int, int);



void entab(char* line, int len, int nspaces) {
    int i = 0, j;
    short seq_spaces = 0;
    for (i = 0; i < len; i++) {
        if (line[i] == ' ') {
            seq_spaces++;
            if (seq_spaces == nspaces) {
                j = i;
                line[j - nspaces + 1] = '\t';
                for (j = j + 1; j < len; j++) {
                    line[j - nspaces + 1] = line[j];
                    line[j] = '\0';
                }
                seq_spaces = 0;
            }
        } else {
            seq_spaces = 0;
        }
    }
}



int main() {
    char line[MAXLINE];
    int len = mygetline(line, MAXLINE);
    printf("%s", line);
    entab(line, len, TAB_IN_SPACES); 
    printf("%s", line);
    return 0;
}

