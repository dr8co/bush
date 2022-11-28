#include <stdlib.h>
#include "main.h"

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
 * @return the string itself.
 */
char *skip_whitespaces(char *s) {
    while (is_space(*s)) ++s;
    return s;
}

/**
 * @brief splits commands and then run them.
 * @param cmdExec - the command to process.
 * @param input - the input.
 * @param first - the first piped command.
 * @param last - the last piped command.
 * @return 1 (SUCCESS) or 0 (FAILURE).
 *
 */
int split(char *cmdExec, int input, int first, int last) {
    char *new_cmd_exec1;
    int m = 1;

    new_cmd_exec1 = _strdup(cmdExec);

    args[0] = _strtok(cmdExec, " ");

    while ((args[m] = _strtok(NULL, " ")) != NULL)
        m++;
    args[m] = NULL;

    for (int i = 0; i < m; ++i) {
        if (args[i][0] == '\"' || args[i][0] == '\'')
            args[i] = skip_quotes(args[i]);
    }

    if (args[0] != NULL) {

        if (_strcmp(args[0], "exit") == 0)
            exit(0);

        if (_strcmp("cd", args[0]) == 0) {
            change_directory();
            free(new_cmd_exec1);
            cmdExec[0] = '\0';
            return 1;
        } else if (_strcmp("pwd", args[0]) == 0) {
            print_working_dir();
            free(new_cmd_exec1);
            cmdExec[0] = '\0';
            return 1;
        }
    }
    int x = command(input, first, last, new_cmd_exec1);
    free(new_cmd_exec1);
    cmdExec[0] = '\0';
    return x;
}
