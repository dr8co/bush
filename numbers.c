#include "main.h"

int _pow(int base, int exponent) {

    int ans = 1;

    while (exponent > 0) {

        int last_bit = (exponent & 1);

        if (last_bit) {
            ans *= base;
        }

        base *= base;
        exponent >>= 1;
    }

    return ans;
}

int _atoi(const char *str) {
    if (str == NULL) {
        return 0;
    }
    int j, i, n = 0, k = 1;
    char *tmp = _strdup(str);

    if (*str == '-') {
        *tmp = '0';
        k = -1;
    }
    i = _strlen(str);

    for (j = 0; j < i; ++j)
        n += (*(tmp + j) - '0') * _pow(10, i - j - 1);

    return n * k;
}