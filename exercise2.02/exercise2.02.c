#include <stdio.h>
#include "utils.h"



/* Rewrite following for loop without using && or ||
 * 
 * for (i = 0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; i++)
 *     s[i] = c;
 */


int main() {
    int i;
    int lim = 100;
    char c;
    char line[lim];

    for (i = 0; i < lim-1; i++) {
        c = getchar();
        if (c == EOF) {
            break; 
        } else {
            line[i] = c;
            if (c == '\n') {
                break;
            }
        }
    }
    
    /* add line ending indicator '\0' */
    line[++i] = '\0';

    printf("Good job, you entered:\n");
    printf("%s", line);

    return 0;
}

