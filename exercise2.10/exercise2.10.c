#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "minunit.h"
#include "exercise2.10.h"


int lower(char s[]) {
    int i = 0;
    while (s[i] != '\0') {
        s[i] >= 65 && s[i] <= 90 ? s[i++] += 32 : i++;
    }
    return 0;
}


#ifdef EXERCISE2_10_TEST
/* TESTS */
int tests_run = 0;


static char * test_lower() {
    char s[] = "!abols13";
    char s1[] = "SANta.^%";
    lower(s);
    lower(s1);
    mu_assert("assertion error, lower('!abols13') != '!abols13'", !strcmp("!abols13", s));
    mu_assert("assertion error, lower('SANta.^%') != 'santa.^%'", !strcmp("santa.^%", s1));
    return 0;
}


static char * all_tests() {
    mu_run_test(test_lower);
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
