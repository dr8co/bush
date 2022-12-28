#include "main.h"
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>


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
 * @return a string of all the matches.
 */
char *expand_globs(const char *string) {
    glob_t globBuff;
    char exp[1024];

    str_cpy(exp, "");
    switch (replace_pattern(string, &globBuff)) {
        case 0:
            for (unsigned int i = 0; i < globBuff.gl_pathc; ++i) {
                str_cat(exp, globBuff.gl_pathv[i]);
                str_cat(exp, " ");
            }
            break;
        case GLOB_NOMATCH:
            str_cpy(exp, string);
            break;
        case GLOB_NOSPACE:
            fprintf(stderr, "No enough memory");
            exit(1);
        case GLOB_ABORTED:
            fprintf(stderr, "Read error");
            exit(1);
    }
    globfree(&globBuff);

    return str_dup(exp);
}
