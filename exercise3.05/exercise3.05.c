#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "minunit.h"
#include "exercise3.05.h"


/*
 * Converts integer n with base 10 to character representation
 * in base b stored in s
 */
void itob(int n, const int b, char s[], size_t sz) {
    if (s == NULL || sz < 1) {
        return;
    }    

    int sign;
    int i = 0;
    int c;
    /* Consider sign */
    if ((sign = n) < 0) {
        n++;
        n = -n;
    }
    /* Convert n in base 10 to base b and store results in s */
    do {
        c = n % b;
        /* Add subtracted 1 back in case n is negative */
        if (i == 0 && sign < 0) {
            c++;
        }
        if (c > 9) {
            s[i++] = '0' + c + 7;
        } else {
            s[i++] = '0' + c;
        }
        n /= b;
    } while (n > 0 && i < sz - 2);

    /* Add - sign if n is negative */
    if (sign < 0) {
        s[i++] = '-';
    }
    
    /* Make it null-terminated string */
    s[i] = '\0';

    /* Reverse array in-place */
    reverse(s, i);
}


#ifdef EXERCISE3_05_TEST
/* TESTS */
int tests_run = 0;


static char * test_itob() {
    char s[100] = { 0 };
    itob(-255, 16, s, 100);
    mu_assert("assertion error, -255 in base 10 is not -FF in base 16", strcmp("-FF", s) == 0);
    itob(255, 8, s, 100);
    mu_assert("assertion error, 255 in base 10 is not 377 in base 8", strcmp("377", s) == 0);
    itob(0, 4, s, 100);
    mu_assert("assertion error, 0 in base 10 is not 0 in base 4", strcmp("0", s) == 0);
    itob(-2147483648, 10, s, 100);
    mu_assert("assertion error, -2147483648 in base 10 is not -2147483648 in base 10",
            strcmp("-2147483648", s) == 0);
    itob(2147483647, 16, s, 100);
    mu_assert("assertion error, 2147483647 in base 10 is not 7FFFFFFF in base 16",
            strcmp("7FFFFFFF", s) == 0);

    return 0;
}


static char * all_tests() {
    mu_run_test(test_itob);
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
