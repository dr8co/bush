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

void exit_shell(int exit_status);

/**
 * @brief the shell entry point.
 * @param argc - argument count.
 * @param argv - argument vector.
 * @return always 0.
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
    int len, status;
    char *cmd = NULL, *cmd2 = NULL;
    char *exit_token[2], exit_buf[1024];

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

        _strcpy(exit_buf, input_buffer);
        exit_token[0] = _strtok(exit_buf, " ");
        exit_token[1] = _strtok(NULL, " ");

        if (_strcmp(exit_token[0], "exit") == 0) {
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

    // Exit with code 128 if the arguments to 'exit' are not valid
    if(!is_numeric(exit_token[1]))
        exit(128);

    // Exit with the provided status
    exit_shell(_atoi(exit_token[1]));
}

/**
 * @brief Exits the shell with an exit code.
 * @param exit_status - the exit code.
 */
void exit_shell(int exit_status){
    // Exit with exit_status % 256 if the exit code is out of range.
    if (exit_status < 0 || exit_status > 255)
        exit_status %= 256;
    exit(exit_status);
}
