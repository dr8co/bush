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
#include <signal.h>
#include <stdio.h>
#include "main.h"

/* Global variables for this file */
char *args[512];
char input_buffer[1024];
extern pid_t pid;
int event_flag;
char his_var[HIST_MAX * 2];
int cmd_count = 0;

void exit_shell(int exit_status);

/**
 * @brief the shell entry point.
 * @param argc - argument count.
 * @param argv - argument vector.
 * @return always 0.
 */
int main(__attribute__((unused)) int argc, char **argv) {
    int len, status;
    char *cmd = NULL, *cmd2 = NULL;
    char *pre_token[2], pre_buf[1024];

    init_shell();

    /* Handle signals e.g Ctrl+C */
    struct sigaction act;
    // Specify the function to handle signals.
    act.sa_handler = &signalHandler;
    // Block all other signals while the signal handler is running.
    sigfillset(&act.sa_mask);

    // Restart functions if interrupted by the signal handler.
    act.sa_flags = SA_RESTART;
    // Handle SIGINT (Ctrl+C) signal
    if (sigaction(SIGINT, &act, NULL) == -1) {
        // If an error occurs, print the error message and exit the shell.
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    // Print help if the shell was called with 'help' argument on the command line.
    if (argv[1]) {
        if (str_cmp(argv[1], "help") == 0)
            find_help(NULL);
    }

    /* The main shell loop to read and execute commands */
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
        str_cpy(input_buffer, cmd2);
        free(cmd);
        free(cmd2);

        if (str_cmp(input_buffer, "") == 0 || input_buffer[0] == '#')
            continue;

        if (input_buffer[0] != '!') {
            read_history();
            write_history();
        }
        len = str_len(input_buffer);
        input_buffer[len - 1] = '\0';
        str_cpy(his_var, input_buffer);

        // Tokenize the first two args for preprocessing.
        str_cpy(pre_buf, input_buffer);
        pre_token[0] = str_tok(pre_buf, " ");
        pre_token[1] = str_tok(NULL, " ");

        // Handle help.
        if (str_cmp(pre_token[0], "help") == 0) {
            find_help(pre_token[1]);
            continue;
        }

        // Exit the shell.
        if (str_cmp(pre_token[0], "exit") == 0) {
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

    if (!pre_token[1])
        pre_token[1] = "0";

    // Exit with code 128 if the arguments to 'exit' are not valid
    if (!is_numeric(pre_token[1]))
        exit(128);

    // Exit with the provided status
    exit_shell(atoi_(pre_token[1]));
}

/**
 * @brief Exits the shell with an exit code.
 * @param exit_status - the exit code.
 */
void exit_shell(int exit_status) {
    // Exit with exit_status % 256 if the exit code is out of range.
    while (exit_status < 0 || exit_status > 255)
        exit_status %= 256;

    exit(exit_status);
}
