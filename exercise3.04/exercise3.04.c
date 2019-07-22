#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "minunit.h"
#include "exercise3.04.h"


void itoa(int n, char s[], size_t sz) {
    int i, sign;
    if ((sign = n) < 0) {
        n = -(n + 1);
    }
    i = 0;
    do {
        if (sign < 0 && i == 0) {
            s[i++] = n % 10 + 1 + '0';
        } else {
            s[i++] = n % 10 + '0';
        }
    } while ((n /= 10) > 0 && i < sz - 2);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0'; 
    reverse(s, i);
}


#ifdef EXERCISE3_04_TEST
/* TESTS */
int tests_run = 0;


static char * test_itoa() {
    char s[50] = { 0 };
    size_t sz = sizeof s / sizeof *s;
    int max_int = ((1 << (sizeof(int) * 8 - 2)) - 1) * 2 + 1;
    itoa(max_int, s, sz);
    mu_assert("assertion error, s != 2147483647", strcmp("2147483647", s) == 0);
    itoa(max_int / 2, s, sz);
    mu_assert("assertion error, s != 1073741823", strcmp("1073741823", s) == 0);
    itoa(~max_int, s, sz);
    mu_assert("assertion error, s != -2147483648", strcmp("-2147483648", s) == 0);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_itoa);
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
