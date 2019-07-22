#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "minunit.h"
#include "exercise3.06.h"


#define INVALID_PARAM "Invalid parameter value"
#define INVALID_PARAMS INVALID_PARAM "s"


int itoa(int n, char s[], size_t sz, size_t min_width)
{
    if (s == NULL || sz == 0) {
        fprintf(stderr, "%s: array is NULL or of size 0, s=%s, sz=%lu\n", INVALID_PARAMS, s, sz);
        return 1;
    }

    if (min_width > sz - 1) {
        fprintf(stderr, "%s: min_width is larger than sz - 1; min_width=%lu, sz=%lu\n",
                INVALID_PARAMS, min_width, sz);
        return 1;
    }

    int c, sign;

    if ((sign = n) < 0) {
        n++;
        n = -n;
    }

    size_t i = 0;
    do {
        if (i >= sz - 2) {
            fprintf(stderr, "Size of array s in not large enough to contain number n\n");
            return 1;
        }
        c = n % 10;
        if (sign < 0 && i == 0)
            c++;
        s[i++] = c + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';
    
    /* Pad left size with blanks if necessary to satisfy min_width */
    while (i < min_width) {
        s[i++] = ' ';
    }

    s[i] = '\0';

    reverse(s, i);

    return 0;
}


#ifdef EXERCISE3_06_TEST
/* TESTS */
int tests_run = 0;


static char * test_itoa() {
    char s[100];

    itoa(0, s, 100, 0);
    mu_assert("assertion error, s != '0'", strcmp(s, "0") == 0);
    itoa(0, s, 100, 12);
    mu_assert("assertion error, s != '           0'", strcmp(s, "           0") == 0);

    itoa(2147483647, s, 100, 0);
    mu_assert("assertion error, s != '2147483647'", strcmp(s, "2147483647") == 0);
    itoa(2147483647, s, 100, 12);
    mu_assert("assertion error, s != '  2147483647'", strcmp(s, "  2147483647") == 0);

    itoa(-2147483648, s, 100, 0);
    mu_assert("assertion error, s != '-2147483648'", strcmp(s, "-2147483648") == 0);
    itoa(-2147483648, s, 100, 12);
    mu_assert("assertion error, s != ' -2147483648'", strcmp(s, " -2147483648") == 0);

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
