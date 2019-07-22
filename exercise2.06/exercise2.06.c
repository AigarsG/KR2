#include <stdio.h>
#include "utils.h"
#include "minunit.h"
#include "exercise2.06.h"


unsigned int setbits(unsigned int x, unsigned int p, unsigned int n, unsigned int y) {
    /* Return x if no bit-set should be done */
    if (n == 0) {
        return x;
    }
    /* Clear all bits to the left side of n rightmost bits of y */
    y = y << (sizeof(y) * 8 - n);
    /* Position n bits of interest opposite bits their replacing */
    y = y >> (sizeof(y) * 8 - (p + 1));
    /* Flip y bits and perform AND operation */
    x = x & ~y;
    /* Get mask for flipping bits to desired state and perform XOR operation with it.
     * PS. I don't know how to explain this but I discovered that XOR operation needs to
     * be performed with a mask of n ON-bits positioned opposite of bits of interest. So after
     * getting n ON-bit mask, it needs to be shifted left by (p + 1 - n) bits before XOR operation
     * or right by (n - p - 1) if n > p + 1 */
    if (n > p + 1) {
        /* We are only interested in p+1 leftmost bits of rightmost set of n bits from y */
        x = x ^ (~(~0 << n) >> (n - (p + 1)));
    } else {
        x = x ^ (~(~0 << n) << (p + 1 - n));
    }
    return x;
}


#ifdef EXERCISE2_06_TEST
/* TESTS */
int tests_run = 0;


static char * test_setbits() {
    mu_assert("assertion error, setbits(146, 4, 4, 78) != 156", setbits(146, 4, 4, 78) == 156);
    mu_assert("assertion error, setbits(0, 0, 1, 255) != 1", setbits(0, 0, 1, 255) == 1);
    mu_assert("assertion error, setbits(3, 1, 4, 4) != 1", setbits(3, 1, 4, 4) == 1);
    mu_assert("assertion error, setbits(56, 3, 0, 13) != 56", setbits(56, 3, 0, 13) == 56);
    mu_assert("assertion error, setbits(240, 7, 1, 254) != 112", setbits(240, 7, 1, 254) == 112);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_setbits);
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
