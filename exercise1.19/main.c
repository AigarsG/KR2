#include <stdio.h>
#define MAXLINE 100



int  getline(char*, int);
void reverse(char*, int);



int getline(char* line, int length) {
    int i = 0;
    char c;
    while ((i < length - 1) && (c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }
    if (c == '\n') {
        line[i++] = c;
    }
    line[i] = '\0';
    return i;
}



void reverse(char* line, int length) {
    int i = 0;
    char c;
    while (--length > i) {
        c = line[length];
        line[length] = line[i];
        line[i++] = c;
    }
}



int main() {
    int len;
    char line[MAXLINE];
    len = getline(line, MAXLINE);
    printf("%s\n", line);
    reverse(line, len);
    printf("%s\n", line);
    return 0;
}

