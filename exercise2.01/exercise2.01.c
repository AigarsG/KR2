#include <stdio.h>
#include <limits.h>
#include <float.h>
#include "utils.h"
#include "exercise2.01.h"
/*#define DEBUG*/



long lpower(int base, int n) {
    long res = 1;
    while (n-- > 0) {
        res *= base;
        if (base > 0 && res < 0) {
            break;
        }

    } 
    return res;
}



int calculate_range(short bytes, short usigned, long *retmin, unsigned long *retmax) {
    int bits = bytes * 8; 
    long res = lpower(2, bits);
    if (usigned) {
        *retmin = 0L;
        if (res < 0) {
            *retmax = -res + -(res + 1); 
        } else {
            *retmax = res - 1;
        }
    } else {
        if (res < 0) {
            *retmin = res;
            *retmax = -(res + 1);
        } else {
            *retmin = -(res / 2);
            *retmax = (res / 2) - 1;
        }
    }
    return 0;
}



int calculate_fp_range(short bytes, long double *min, long double *max) {
    if (bytes % 2 != 0) {
        printf("Error, %d bytes passed, expected 4 or 8\n", bytes);
        return 1;
    } else {
        short ebits;
        short fbits;
        long maxexp;
        long minexp;
        if (bytes == 4) {
            /* single-precision floating point */
            ebits = 8;
            fbits = 23;
        } else if (bytes == 8) {
            /* double-precision floating point */
            ebits = 11;
            fbits = 52;
        } else {
            /* quadruple-precision floating point */
            ebits = 15;
            fbits = 113;
        }

        /* calculate exponents */
        maxexp = (lpower(2, ebits) - 1) / 2;
        minexp = -1L * maxexp + 1L;
#ifdef DEBUG
        printf("maxexp=%ld, minexp=%ld\n", maxexp, minexp);
#endif

        /* calculate max */
        *max = 1.0L;
        while (fbits > 0) {
            *max /= 2.0L;
            fbits--;
        }
        *max = (2.0L - *max);
        while (maxexp > 0) {
            *max *= 2.0L;
            maxexp--;
        }

        /* calculate min */
        *min = 1.0L;
        while (minexp < 0) {
            *min /= 2.0L;
            minexp++;
        }

        return 0;
    }
}



int main() {
    long min;
    unsigned long max;
    long double fpmin;
    long double fpmax;
    short bytes = sizeof(char);

    calculate_range(bytes, 0, &min, &max);
    printf("signed char, min = %ld, max = %ld; min=%d, max=%d\n", min, max, SCHAR_MIN, SCHAR_MAX);
    calculate_range(bytes, 1, &min, &max);
    printf("unsigned char, min = %ld, max = %ld; min=%d, max=%d\n", min, max, CHAR_MIN, CHAR_MAX);

    bytes = sizeof(short);
    calculate_range(bytes, 0, &min, &max);
    printf("signed short, min = %ld, max = %ld; min=%d, max=%d\n", min, max, SHRT_MIN, SHRT_MAX);
    calculate_range(bytes, 1, &min, &max);
    printf("unsigned short, min = %ld, max = %ld; min=%d, max=%d\n", min, max, 0, USHRT_MAX);

    bytes = sizeof(int);
    calculate_range(bytes, 0, &min, &max);
    printf("signed int, min = %ld, max = %ld; min=%d, max=%d\n", min, max, INT_MIN, INT_MAX);
    calculate_range(bytes, 1, &min, &max);
    printf("unsigned int, min = %ld, max = %ld; min=%d, max=%ld\n", min, max, 0, UINT_MAX);

    bytes = sizeof(long);
    calculate_range(bytes, 0, &min, &max);
    printf("signed long, min = %ld, max = %ld; min=%ld, max=%ld\n", min, max, LONG_MIN, LONG_MAX);
    calculate_range(bytes, 1, &min, &max);
    printf("unsigned long, min = %ld, max = %lu; min=%d, max=%lu\n", min, max, 0, ULONG_MAX);

    bytes = sizeof(float);
    calculate_fp_range(bytes, &fpmin, &fpmax);
    printf("single precision floating-point, min=%Lf, max=%Lf; min=%f, max=%f\n", fpmin, fpmax, FLT_MIN, FLT_MAX);

    bytes = sizeof(double);
    calculate_fp_range(bytes, &fpmin, &fpmax);
    printf("double precision floating-point, min=%Lf, max=%Lf; min=%f, max=%f\n", fpmin, fpmax, DBL_MIN, DBL_MAX);

    bytes = sizeof(long double);
    calculate_fp_range(bytes, &fpmin, &fpmax);
    printf("double precision floating-point, min=%Lf, max=%Lf; min=%Lf, max=%Lf\n", fpmin, fpmax, LDBL_MIN, LDBL_MAX);



    return 0;
}

