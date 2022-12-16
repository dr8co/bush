#include "main.h"
#include <glob.h>
#include <stdio.h>

char *expanded[1024];

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

int replace_pattern(const char *str, glob_t *glob_buf) {
    return (glob(str, GLOB_ERR | GLOB_APPEND, NULL, glob_buf));
}

int expand_globs(const char *string) {
    glob_t globBuff;

    replace_pattern(string, &globBuff);

    for (unsigned int i = 0; i < globBuff.gl_pathc; ++i) {
        expanded[i] = globBuff.gl_pathv[i];
        printf("%s\n", globBuff.gl_pathv[i]);
    }
    globfree(&globBuff);

    return globBuff.gl_pathc != 0 ? 0 : 1;
}
