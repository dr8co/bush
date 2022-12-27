#include "main.h"
#include <glob.h>
#include <stdio.h>

char *expanded[1024];

/**
 * @brief Check if a string contains a wildcard character.
 * @param str the string to check.
 * @return 1 if a wildcard character is present, 0 otherwise.
 */
int has_wildcard(const char *str) {
    if (!str)
        return 0;

    for (unsigned int i = 0; *(str + i) != '\0'; ++i) {
        if (*(str + i) == '*' || *(str + i) == '?')
            return 1;

        if (*(str + i) == '[') {
            for (unsigned int j = i + 1; *(str + j) != '\0' && !is_space(*(str + j)); ++j) {
                if (*(str + j) == ']')
                    return 1;
            }
        }
    }
    return 0;
}

/**
 * @brief Replaces a wildcard pattern with matches.
 * @param str a string containing a wildcard character.
 * @param glob_buf a buffer to store the matches.
 * @return 0 on success, others in failure
 * (see documentation of 'glob' function, e.g `man 3 glob`).
 */
int replace_pattern(const char *str, glob_t *glob_buf) {
    return (glob(str, GLOB_ERR | GLOB_APPEND, NULL, glob_buf));
}

/**
 * @brief expand wildcards in a string to successful matches.
 * @param string the string with wildcards to be expanded.
 * @return 0 on success, -1 if no matches were found.
 */
int expand_globs(const char *string) {
    glob_t globBuff;

    replace_pattern(string, &globBuff);

    for (unsigned int i = 0; i < globBuff.gl_pathc; ++i) {
        expanded[i] = globBuff.gl_pathv[i];
        printf("%s\n", globBuff.gl_pathv[i]);
    }
    globfree(&globBuff);

    return globBuff.gl_pathc != 0 ? 0 : -1;
}
