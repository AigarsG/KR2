#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "utils.h"
#include "minunit.h"
#include "exercise4.01.h"


ssize_t strrindex(const char *s, const char *t)
{
    if (s == NULL || t == NULL) {
        fprintf(stderr, "Invalid parameters\n");
        return -1;
    }
    ssize_t ret = -1;
    size_t slen = strlen(s);
    size_t tlen = strlen(t);
    ssize_t i, j, k;

    if (tlen > slen) {
        return -1;
    }

    for (i = slen - 1; i >= 0; i--) {
        for (j = tlen - 1, k = i; j >= 0; j--, k--) {
            if (s[k] != t[j]) {
                break;
            }
        }
        /* 
         * If full string matches, starting position of right-most substring t
         * will be at position i + 1 
         */
        if (j < 0) {
            ret = k + 1;
            break;
        }
    }

    return ret;
}


#ifdef EXERCISE4_01_TEST
/* TESTS */
int tests_run = 0;


static char * test_strrindex() {
    ssize_t idx;
    idx = strrindex("this is amazing", "blah");
    mu_assert("assertion error, strrindex(\"this is amazing\", \"blah\") != -1", idx == -1);
    idx = strrindex("this is amazing", "is");
    mu_assert("assertion error, strrindex(\"this is amazing\", \"is\") != 5", idx == 5);
    idx = strrindex("this is amazing", "zing");
    mu_assert("assertion error, strrindex(\"this is amazing\", \"zing\") != 11", idx == 11);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_strrindex);
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
#endif
