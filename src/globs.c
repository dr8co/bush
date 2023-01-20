#include "main.h"
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Check if a string contains a wildcard character.
 * @param str the string to check.
 * @return 1 if a wildcard character is present, 0 otherwise.
 * @note This is a minimal function, and might return 1 for a string
 * without a wildcard character.
 */
int has_wildcard(const char *str) {
    if (!str)
        return 0;

    for (unsigned int i = 0; *(str + i) != '\0'; ++i) {
        if (*(str + i) == '*' || *(str + i) == '?')
            return 1;

        if (*(str + i) == '[') {
            for (unsigned int j = i + 2; *(str + j) != '\0' && !is_space(*(str + j)); ++j) {
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
    return (glob(str, GLOB_ERR, NULL, glob_buf));
}

/**
 * @brief expand wildcards in a string to successful matches.
 * @param string the string with wildcards to be expanded.
 * @return an array of strings that match the wildcard(s).
 */
char **expand_globs(const char *string) {
    glob_t globBuff;
    char **exp;
    size_t i = 0;
    int ret;

    ret = replace_pattern(string, &globBuff);
    exp = malloc(sizeof(char *) * 4096);

    switch (ret) {
        case 0:
            for (; i < globBuff.gl_pathc; ++i) {
                exp[i] = str_dup(globBuff.gl_pathv[i]);
            }
            exp[i] = NULL;
            break;
        case GLOB_NOMATCH:
            exp[0] = str_dup(string);
            exp[1] = NULL;
            break;
        case GLOB_NOSPACE:
            fprintf(stderr, "No enough memory\n");
            exit(-1);
        case GLOB_ABORTED:
            fprintf(stderr, "Read error\n");
            exit(-1);
        default:
            fprintf(stderr, "Something went wrong\n");
            exit(-1);
    }
    globfree(&globBuff);

    return exp;
}

/**
 * @brief finds wildcards in args[] and expands them to successful matches.
 */
void process_globs() {
    char **expanded, **args_expanded;

    for (int i = 0; args[i]; ++i) {
        if (has_wildcard(args[i])) {
            expanded = expand_globs(args[i]);

            args_expanded = merge_arrays(args, expanded, i);
            remove_element(args_expanded, i);

            for (int j = 0; args_expanded[j]; ++j) {
                args[j] = str_dup(args_expanded[j]);
            }

            for (int k = 0; expanded[k]; ++k) {
                free(expanded[k]);
            }

            free(expanded);
            free(args_expanded);
        }
    }
}
