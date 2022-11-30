/**
 * @file strings_2.c
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
 * @brief replaces a substring in a string.
 * @param str - the parent string.
 * @param old - the substring in str to be replaced.
 * @param new - the string to replace old in str.
 * @return a new str with the old replaced by new.
 */
char *replace_str(const char *str, const char *old, const char *new) {
    char *result;
    int i, count = 0;
    int new_len = _strlen(new);
    int old_len = _strlen(old);

    // Count the number of times old word occurs in the string
    for (i = 0; str[i] != '\0'; ++i) {
        if (_strstr(&str[i], old) == &str[i]) {
            ++count;

            // Jump to index after the old word.
            i += old_len - 1;
        }
    }

    // Resize the new string
    result = (char *) malloc(i + count * (new_len - old_len) + 1);

    i = 0;
    while (*str) {
        // compare the substring with the result
        if (_strstr(str, old) == str) {
            _strcpy(&result[i], new);
            i += new_len;
            str += old_len;
        } else
            result[i++] = *str++;
    }

    result[i] = '\0';
    return result;
}


/**
 * @brief tokenizes a string but not within enclosed texts.
 * @param str - the string to tokenize.
 * @param delim - the delimiter.
 * @return a pointer to the next token or NULL.
 */
char *strtok_skip(char *str, char *delim) {
    static char *token = NULL;
    char *lead = NULL;
    char *block = NULL;
    char open_b[] = {"\"[<{"};
    char close_b[] = {"\"]>}"};

    int iBlock = 0;
    int iBlockIndex = 0;

    if (str != NULL) {
        token = str;
        lead = str;
    } else {
        lead = token;
        if (*token == '\0') {
            lead = NULL;
        }
    }

    while (*token != '\0') {
        if (iBlock) {
            if (close_b[iBlockIndex] == *token) {
                iBlock = 0;
            }
            ++token;
            continue;
        }
        if ((block = _strchr(open_b, *token)) != NULL) {
            iBlock = 1;
            iBlockIndex = block - open_b;
            ++token;
            continue;
        }
        if (_strchr(delim, *token) != NULL) {
            *token = '\0';
            ++token;
            break;
        }
        ++token;
    }
    return lead;
}

/**
 * @brief removes quotation marks from a string.
 * @param str - the string to process.
 * @return a string without quotation marks.
 */
char *skip_quotes(const char *str) {
    int i = 0, j = 0;
    char temp[1024];
    while (str[i++] != '\0') {
        if (str[i - 1] != '"')
            temp[j++] = str[i - 1];
    }
    temp[j] = '\0';
    return _strdup(temp);
}

/**
 * @brief checks if a character is a whitespace.
 * @param c - the character to check.
 * @return 1 if character is a whitespace, 0 otherwise.
 */
int is_space(int c) {
    return (c == '\t' || c == '\n' ||
            c == '\v' || c == '\f' || c == '\r' || c == ' ' ? 1 : 0);
}

/**
 * @brief skips whitespaces in a string.
 * @param s - the string to process.
 * @return a pointer to the first character after whitespace.
 */
char *skip_whitespaces(char *s) {
    while (is_space(*s)) ++s;
    return s;
}

/**
 * @brief trim leading and trailing whitespaces from a string
 * except the last trailing whitespace. (for the 'enter' after command input).
 * @param str - the string to process.
 * @return string without leading whitespaces and with one trailing
 * whitespace, if one existed before.
 */
char *trim_leading_trailing(const char *str) {
    int i = 0, k = 0, l;
    char *str2;

    if (!str)
        return NULL;

    l = _strlen(str);
    str2 = malloc(sizeof(char) * l + 2);

    while (is_space(str[i]))
        ++i;

    while (is_space(str[l - 1]))
        --l;

    for (int j = i; j <= l; ++j) {
        str2[k] = str[j];
        ++k;
    }

    str2[k] = '\0';

    return str2;
}
