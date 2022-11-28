#include <stdlib.h>
#include "main.h"

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

    args[0] = strtok_skip(cmdExec, " ");

    while ((args[m] = strtok_skip(NULL, " ")) != NULL) {
        ++m;
    }
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
