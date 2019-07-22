#include <stdio.h>
#include "utils.h"
#include "minunit.h"
#include "exercise2.05.h"


int any(const char *s1, const char *s2) {
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) {
                return i;
            }
        }
    }
    return -1;
}


/* TESTS */
int tests_run = 0;


static char * test_any_positive() {
    char *s1 = "test string";
    char *s2 = "t g";
    char *s3 = " i";
    char *s4 = "mhg";
    mu_assert("assertion error in test_any_positive, any(s1, s2) != 0", any(s1, s2) == 0);
    mu_assert("assertion error in test_any_positive, any(s1, s3) != 4", any(s1, s3) == 4);
    mu_assert("assertion error in test_any_positive, any(s1, s4) != 10", any(s1, s4) == 10);
    return 0;
}


static char * test_any_negative() {
    char *s1 = "test string";
    char *s2 = "mhj";
    mu_assert("assertion error in test_any_negative, any(s1, s2)", any(s1, s2) == -1);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_any_positive);
    mu_run_test(test_any_negative);
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
