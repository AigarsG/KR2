#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "minunit.h"
#include "exercise2.04.h"


int squeeze(char s1[], const char s2[]) {
    int i, j, k, is;
    for (i = j = 0; s1[i] != '\0'; i++) {
        k = is = 0;
        while (s2[k] != '\0') {
            if (s1[i] == s2[k]) {
                is = 1;
                break;
            }
            k++;
        }
        if (!is) {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
    return 0;
}


/* TESTS */
int tests_run = 0;


static char * test_squeeze() {
    char s1[] = "bloddy hell";
    char *s2 = " dl";
    const char *exp = "boyhe";
    squeeze(s1, s2);
    mu_assert("assertion error, squeeze(s1, s2) != 'boyhe'", strcmp(exp, s1) == 0);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_squeeze);
    return 0;
}


int main() {
    char * result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Test run: %d\n", tests_run);
    return result != 0;
}

