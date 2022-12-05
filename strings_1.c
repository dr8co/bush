/**
 * @file strings_1.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for string operations
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"
#include <stdlib.h>

/**
 * @brief calculates length of a string.
 * @param s - input string.
 * @return the length of a string or 0 if string is NULL.
 */
int str_len(const char *s) {
    int l = 0;

    if (!s)
        return (l);

    while (*s != '\0') {
        ++s;
        ++l;
    }
    return (l);
}

/**
 * @brief copies string pointed to by src to string pointed to by dest.
 * @param dest - destination.
 * @param src - string to copy.
 * Return: a pointer to the destination.
 */
char *str_cpy(char *dest, const char *src) {
    int i;
    if (!src)
        return NULL;

    for (i = 0; src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return (dest);
}

/**
 * @brief compares two strings.
 * @param s1 - first string.
 * @param s2 - second string.
 *
 * @return the difference of s1 and s2.
 */
int str_cmp(const char *s1, const char *s2) {
    int i = 0;

    while (*(s1 + i) && *(s2 + i) && (*(s1 + i) == *(s2 + i)))
        ++i;
    return (*(s1 + i) - *(s2 + i));
}

/**
 * @brief appends src string to the dest string
 * @param dest - string to append by src
 * @param src - string to append to dest
 *
 * @eturn: pointer to the resulting string dest,
 * or NULL if both strings are not present or NULL.
 */
char *str_cat(char *dest, char *src) {
    int i, j;

    if (!dest && !src) {
        return NULL;
    } else if (!dest) {
        return src;
    } else if (!src) {
        return dest;
    }
    i = j = 0;
    while (*(dest + i))
        ++i;
    while ((*(dest + i) = *(src + j))) {
        ++i;
        ++j;
    }
    return (dest);
}

/**
 * @brief locates a character in a string.
 * @param s - the string to check.
 * @param c - the character to check for.
 *
 * @return a pointer to first occurrence of c in s or NULL.
 */
char *str_chr(char *s, char c) {
    int i;

    for (i = 0; *(s + i); ++i) {
        if (*(s + i) == c)
            return (s + i);
    }
    if (*(s + i) == c)
        return (s + i);

    return (0);
}

/**
 * @brief copies a string given as parameter.
 * @param str - the string to be duplicated.
 *
 * @return a pointer to the copied string (Success), NULL (Error).
 */
char *str_dup(const char *str) {
    char *duplicate;
    unsigned int i, l;

    i = 0;
    l = str_len(str);

    if (str == NULL)
        return (NULL);

    duplicate = (char *) malloc(sizeof(char) * (l + 1));

    if (duplicate == NULL)
        return (NULL);

    while ((duplicate[i] = str[i]) != '\0')
        ++i;

    return (duplicate);
}

/**
 * @brief checks if a string contains a character.
 * @param c - the character to check.
 * @param str: the string to check.
 * @return: 1 (SUCCESS), 0 (FAILURE).
 */
unsigned int check_delim(char c, const char *str) {
    unsigned int i;

    for (i = 0; str[i] != '\0'; ++i) {
        if (c == str[i])
            return (1);
    }
    return (0);
}

/**
 * @brief splits a string into tokens.
 * @param str: the string to split.
 * @param delim: the delimiter.
 * @return: a pointer to the next token or NULL.
 */
char *str_tok(char *str, const char *delim) {
    static char *ts;
    static char *nt;
    unsigned int i;

    if (str != NULL)
        nt = str;
    ts = nt;
    if (ts == NULL)
        return (NULL);
    for (i = 0; ts[i] != '\0'; ++i) {
        if (!check_delim(ts[i], delim))
            break;
    }
    if (nt[i] == '\0' || nt[i] == '#') {
        nt = NULL;
        return (NULL);
    }
    ts = nt + i;
    nt = ts;
    for (i = 0; nt[i] != '\0'; ++i) {
        if (check_delim(nt[i], delim))
            break;
    }
    if (nt[i] == '\0')
        nt = NULL;
    else {
        nt[i] = '\0';
        nt = nt + i + 1;
        if (*nt == '\0')
            nt = NULL;
    }
    return (ts);
}

/**
 * @brief locates a substring.
 * @param haystack - string in which to check for needle.
 * @param needle - substring to find in haystack.
 *
 * @return a pointer to beginning of needle in haystack or NULL if no match.
 */
char *str_str(const char *haystack, const char *needle) {
    unsigned int i = 0, j = 0;

    while (haystack[i]) {
        while (needle[j] && (haystack[i] == needle[0])) {
            if (haystack[i + j] == needle[j])
                ++j;
            else
                break;
        }
        if (needle[j]) {
            ++i;
            j = 0;
        } else
            return (char *) (haystack + i);
    }
    return (0);
}
