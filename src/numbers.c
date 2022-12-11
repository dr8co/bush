/**
 * @file numbers.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for numerical computations
 * @version 1.0
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdlib.h>
#include "main.h"

/**
 * @brief performs exponentiation of integers.
 * @param base - the base
 * @param exponent - the exponent
 * @return base to the power of the exponent.
 */
int pow_(int base, int exponent) {

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

/**
 * @brief Checks if a string is numeric.
 * @param str - the string to check.
 * @return 1 if the string is numeric, 0 otherwise.
 */
int is_numeric(const char *str)
{
    while(*str != '\0')
    {
        if(*str < '0' || *str > '9')
            return 0;
        str++;
    }
    return 1;
}

/**
 * @brief converts a string to an integer.
 * @param str - the string to convert.
 * @return the string as an integer.
 */
int atoi_(const char *str) {
    if (str == NULL || !is_numeric(str))
        return 0;

    int j, i, n = 0, k = 1;
    char *tmp = str_dup(str);

    if (*str == '-') {
        *tmp = '0';
        k = -1;
    }
    i = str_len(str);

    for (j = 0; j < i; ++j)
        n += (*(tmp + j) - '0') * pow_(10, i - j - 1);
    free(tmp);

    return n * k;
}
