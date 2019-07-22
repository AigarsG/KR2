#include <stdio.h>
#include "utils.h"
#include "minunit.h"
#include "exercise2.06.h"
#include "exercise2.07.h"


unsigned int invert(unsigned int x, unsigned int p, unsigned int n) {
    /* Return x if no bits should be inverted */
    if (n == 0) {
        return x;
    } 
    /* use getbits to get the bits of interest, invert them and use setbits to set inverted bits */    
    return setbits(x, p, n, ~getbits(x, p, n));
}


#ifdef EXERCISE2_07_TEST
/* TESTS */
int tests_run = 0;


static char * test_invert() {
    mu_assert("assertion error, invert(46, 4, 3) != 50", invert(46, 4, 3) == 50);
    mu_assert("assertion error, invert(24, 4, 5) != 7", invert(24, 4, 5) == 7);
    mu_assert("assertion error, invert(65536, 16, 17) != 65535", invert(65536, 16, 17) == 65535);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_invert);
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
