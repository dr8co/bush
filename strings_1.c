#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief calculates length of a string.
 * @param s - input string.
 * @return the length of a string or 0 if string is NULL.
 */
int _strlen(const char *s) {
    int l = 0;

    if (!s)
        return (l);

    while (*s != '\0') {
        s++;
        l++;
    }
    return (l);
}

/**
 * @brief copies string pointed to by src to string pointed to by dest.
 * @param dest - destination.
 * @param src - string to copy.
 * Return: a pointer to the destination.
 */
char *_strcpy(char *dest, const char *src) {
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
int _strcmp(const char *s1, const char *s2) {
    int i = 0;

    while (*(s1 + i) && *(s2 + i) && (*(s1 + i) == *(s2 + i)))
        i++;
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
char *_strcat(char *dest, char *src) {
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
        i++;
    while ((*(dest + i) = *(src + j))) {
        i++;
        j++;
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
char *_strchr(char *s, char c) {
    int i;

    for (i = 0; *(s + i); i++) {
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
char *_strdup(const char *str) {
    char *duplicate;
    unsigned int i, l;

    i = 0;
    l = _strlen(str);

    if (str == NULL)
        return (NULL);

    duplicate = (char *) malloc(sizeof(char) * (l + 1));

    if (duplicate == NULL)
        return (NULL);

    while ((duplicate[i] = str[i]) != '\0')
        i++;

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

    for (i = 0; str[i] != '\0'; i++) {
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
char *_strtok(char *str, const char *delim) {
    static char *ts;
    static char *nt;
    unsigned int i;

    if (str != NULL)
        nt = str;
    ts = nt;
    if (ts == NULL)
        return (NULL);
    for (i = 0; ts[i] != '\0'; i++) {
        if (!check_delim(ts[i], delim))
            break;
    }
    if (nt[i] == '\0' || nt[i] == '#') {
        nt = NULL;
        return (NULL);
    }
    ts = nt + i;
    nt = ts;
    for (i = 0; nt[i] != '\0'; i++) {
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
char *_strstr(const char *haystack, const char *needle) {
    unsigned int i = 0, j = 0;

    while (haystack[i]) {
        while (needle[j] && (haystack[i] == needle[0])) {
            if (haystack[i + j] == needle[j])
                j++;
            else
                break;
        }
        if (needle[j]) {
            i++;
            j = 0;
        } else
            return (char *) (haystack + i);
    }
    return (0);
}

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
    for (i = 0; str[i] != '\0'; i++) {
        if (_strstr(&str[i], old) == &str[i]) {
            count++;

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
            token++;
            continue;
        }
        if ((block = _strchr(open_b, *token)) != NULL) {
            iBlock = 1;
            iBlockIndex = block - open_b;
            token++;
            continue;
        }
        if (_strchr(delim, *token) != NULL) {
            *token = '\0';
            token++;
            break;
        }
        token++;
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
