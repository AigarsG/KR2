#include <stdio.h>
#define TAB_IN_SPACES 8
#define MAXLINE 1000



int getline(char*, int);
int detab(char*, int, int, int, int);
int tabcount(char*, int);



int getline(char* line, int maxlen) {
    int i = 0;
    char c;
    while ((i < maxlen - 1) && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}



int detab(char* line, int length, int maxlen, int ntabs, int nspaces) {
    int max_space_needed = (length - ntabs) + ntabs * nspaces;
    if (max_space_needed > maxlen) {
        printf("Unable to replace %d tabs with %d spaces, maximum length %d exceeded by %d\n",
                ntabs, ntabs * nspaces, maxlen, max_space_needed - maxlen);
        return -1;
    }
    int i = 0, j, tabs = 0;
    char c;
    while (i < length && tabs < ntabs) {
        c = line[i];
        if (c == '\t') {
            /* Shift characters to free space for blanks */
            j = length - 1;
            while (j > i) {
                line[j + (nspaces - 1)] = line[j];
                j--;
            }
            /* Insert spaces instead of tab */
            for (j = i; j < i + nspaces; j++) {
                line[j] = ' ';
            }
            /* increase line length */
            length += nspaces;
            tabs++;
        }
        i++;
    }
    return length;
}



int tabcount(char* line, int len) {
    int i, ret = 0;
    for (i = 0; i < len; i++) {
        if (line[i] == '\t') {
            ret++;
        }
    }
    return ret;
}



int main() {
    char line[MAXLINE];
    int len = getline(line, MAXLINE);
    detab(line, len, MAXLINE, tabcount(line, len), TAB_IN_SPACES);
    printf("%s", line);

    return 0;
}

