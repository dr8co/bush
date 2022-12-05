/**
 * @file process_cmd.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for functions to process commands
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */

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

    new_cmd_exec1 = str_dup(cmdExec);

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

        if (str_cmp(args[0], "exit") == 0)
            exit(0);

        if (str_cmp("cd", args[0]) == 0) {
            change_directory();
            free(new_cmd_exec1);
            cmdExec[0] = '\0';
            return 1;
        } else if (str_cmp("pwd", args[0]) == 0) {
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
