#include <stdio.h>
#include "utils.h"
#include "minunit.h"
#include "exercise3.01.h"


int binsearch(const int x, const int v[], const int n) {
    int ret = -1;
    int l = 0;
    int r = n - 1;
    int mid;

    while (l < r) {
        mid = (l + r) / 2 + 1;
        if (v[mid] > x) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }

    if (x == v[l]) {
        ret = l;
    }

    return ret;
}


#ifdef EXERCISE3_01_TEST
/* TESTS */
int tests_run = 0;


static char * test_binsearch() {
    const int v[] = {-1013, -231, -111, -34, 0,
                     1, 2, 3, 4, 6, 11, 23, 65,
                     81, 82, 83, 90, 103, 113, 114,
                     234, 543, 550, 633, 777, 1001};
    const int n = sizeof v / sizeof(*v);
    mu_assert("assertion error, binsearch(-1014, v, n) != -1", binsearch(-1014, v, n) == -1);
    mu_assert("assertion error, binsearch(-1013, v, n) != 0", binsearch(-1013, v, n) == 0);
    mu_assert("assertion error, binsearch(-111, v, n) != 2", binsearch(-111, v, n) == 2);
    mu_assert("assertion error, binsearch(-1, v, n) != -1", binsearch(-1, v, n) == -1);
    mu_assert("assertion error, binsearch(1, v, n) != 5", binsearch(1, v, n) == 5);
    mu_assert("assertion error, binsearch(90, v, n) != 16", binsearch(90, v, n) == 16);
    mu_assert("assertion error, binsearch(113, v, n) != 18", binsearch(113, v, n) == 18);
    mu_assert("assertion error, binsearch(1000, v, n) != -1", binsearch(1000, v, n) == -1);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_binsearch);
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
