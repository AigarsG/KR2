#include <stdio.h>
#include "utils.h"
#include "minunit.h"
#include "exercise2.09.h"


unsigned int onebitcount(unsigned int x) {
    unsigned int ret = 0;
    while (x > 0) {
        ret++;
        /* In two's complement, x & (x - 1) removes the first rightmost 1-bit.
         * Performing XOR operation with the result and x yields value that 
         * should be subtracted from x in normal form. */
        x -= ((~x + 1) ^ ((~x + 1) & ~x));
    }
    return ret;
}


#ifdef EXERCISE2_09_TEST
/* TESTS */
int tests_run = 0;


static char * test_1bitcount() {
    mu_assert("assertion error, onebitcount(152) != 3", onebitcount(152) == 3);
    mu_assert("assertion error, onebitcount(541) != 5", onebitcount(541) == 5);
    mu_assert("assertion error, onebitcount(127) != 7", onebitcount(127) == 7);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_1bitcount);
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
