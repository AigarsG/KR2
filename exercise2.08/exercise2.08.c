#include <stdio.h>
#include "utils.h"
#include "minunit.h"
#include "exercise2.08.h"


static unsigned int bitcount(unsigned x) {
    unsigned int ret = 0;
    while (x > 0) {
        ret++;
        x >>= 1;
    }
    return ret;
}


unsigned int rightrot(unsigned int x, unsigned int n) {
    /* Return x if no rotation should be done */
    if (n == 0) {
        return x;
    }
    unsigned int nbits = bitcount(x);
    /* If n > bitcount, rotate by bitcount until n < bitcount :) */
    n %= nbits;
    return ((x >> n) | (getbits(x, n-1, n) << (nbits - n)));
}


#ifdef EXERCISE2_08_TEST
/* TESTS */
int tests_run = 0;


static char * test_rightrot() {
    mu_assert("assertion error, rightrot(6, 3) != 6", rightrot(6, 3) == 6);
    mu_assert("assertion error, rightrot(6, 4) != 3", rightrot(6, 4) == 3);
    mu_assert("assertion error, rightrot(6, 5) != 5", rightrot(6, 5) == 5);
    mu_assert("assertion error, rightrot(6, 6) != 6", rightrot(6, 6) == 6);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_rightrot);
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
