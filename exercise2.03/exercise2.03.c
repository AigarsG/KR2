#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "utils.h"
#include "minunit.h"


int tests_run = 0;


static int hex2int(char hex, int i) {
    hex = tolower(hex);
    assert(isdigit(hex) || (hex >= 'a' && hex <= 'f'));
    int ret;
    int multiply = 1;
    while (i-- > 0) {
        multiply *= 16;
    }
    ret = hex - '0';
    if (isdigit(hex)) {
        ret *= multiply;
    } else {
        /* 'a' is 97, '0' is 48, so (a)h = 10 = 97 - 48 - 39 */ 
        ret = (ret - 39) * multiply;
    }
    return ret;
}


static int adjust_for_0x(char *s, unsigned int *sz) {
    if (*sz > 1) {
        /* Verify that in case string starts with 0X or 0x then it must have another character followed by */
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            assert(*sz > 2);
            /* Shift characters by 2 to the left */
            shift_left(s, sz, 2);
        }
    }
    return 0; 
}


static int adjust_for_minus(char *s, unsigned int *sz, int *ret_minus_state) {
    if (s[0] == '-') {
        *ret_minus_state = 1;
        /* Shift all charactrs to left by 1 */
        shift_left(s, sz, 1);
    }
    return 0;
}


int htoi(const char *s, const unsigned int sz) {
    assert(sz > 0);
    unsigned int i;
    int n;
    int res = 0;
    int has_minus = 0;
    unsigned int sz2 = sz;
    char copy[sz];

    /* Make copy of original hex string */
    memset(copy, '\0', sz);
    strcpy(copy, s);

    /* Adjust in case hex string has minus sign in front of it */ 
    adjust_for_minus(copy, &sz2, &has_minus);

    /* Adjust in case hex has 0x or 0X prefix */
    adjust_for_0x(copy, &sz2);

    /* Iterate over each character in string of hexadecimal number and convert it to its integer
     * counterpart and add it to the end result integer. */
    for (i = 0; i < sz2; i++) {
        n = hex2int(copy[i], sz2-(i+1));   
        res += n;
    }

    if (has_minus) {
        res = -res;
    }

    return res;
}


static char * test_htoi() {
    int res = htoi("0xF4a", 5);
    mu_assert("assertion error, 0xF4a != 3914", res == 3914);
    res = htoi("-ab", 3);
    mu_assert("assertion error, -ab != -171", res == -171);
    res = htoi("-0XfA", 5);
    mu_assert("assertion error, -0XfA != -250", res == -250);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_htoi);
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

