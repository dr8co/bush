/**
 * @file main.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief entry point to the shell
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"

/* Global variables for this file */
char *args[512];
char input_buffer[1024];
extern pid_t pid;
int event_flag;
char his_var[2048];
int cmd_count = 0;

/**
 * @brief the shell entry point.
 * @param argc - argument count.
 * @param argv - argument vector.
 * @return always 0.
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
    int flag = 0, len, status;
    char *cmd = NULL, *cmd2 = NULL;

    init_shell();
    signal(SIGINT, signalHandler);

    while (1) {
        clear_variables();
        print_prompt1();
        cmd = read_cmd();

        if (cmd) {
            ++cmd_count;
            cmd2 = trim_leading_trailing(cmd);
        } else {
            exit(0);
        }
        _strcpy(input_buffer, cmd2);
        free(cmd);
        free(cmd2);

        if (_strcmp(input_buffer, "\n") == 0 || input_buffer[0] == '#')
            continue;

        if (input_buffer[0] != '!') {
            read_history();
            write_history();
        }
        len = _strlen(input_buffer);
        input_buffer[len - 1] = '\0';
        _strcpy(his_var, input_buffer);

        if (_strcmp(input_buffer, "exit") == 0 || _strcmp(input_buffer, "exit\n") == 0) {
            flag = 1;
            break;
        }

        if (input_buffer[0] == '!') {
            read_history();
            event_flag = 1;
            free_histfile();
            execute_event();
        }
        execute_pipe();
        waitpid(pid, &status, 0);
    }

    free_global_vars();

    if (flag == 1) {
        exit(0);
    }
    return 0;
}
