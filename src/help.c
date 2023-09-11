/**
 * @file help.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for help-related functions.
 * @version 3.0
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include "main.h"

/* Help Messages */
extern char *cd_msg, *echo_msg;
extern char *exit_msg, *help_msg;
extern char *history_msg, *export_msg, *help_help, *version;

/**
 * @brief Prints help message to stdout.
 * @param str the command whose help message is printed.
 */
void print_help(const char *str) {
    if (str == NULL)
        printf("%s\n", help_msg);
    else {
        if (str_cmp(str, "cd") == 0)
            printf("%s\n", cd_msg);
        else if (str_cmp(str, "echo") == 0)
            printf("%s\n", echo_msg);
        else if (str_cmp(str, "exit") == 0)
            printf("%s\n", exit_msg);
        else if (str_cmp(str, "history") == 0)
            printf("%s\n", history_msg);
        else if (str_cmp(str, "export") == 0)
            printf("%s\n", export_msg);
        else if (str_cmp(str, "help") == 0)
            printf("%s\n", help_help);
        else if (str_cmp(str, "version") == 0)
            printf("%s\n", version);
        else if (str_cmp(str, "license") == 0)
            printf("%s\n", LICENSE);
        else
            printf("The Burning Bush: help: no help topics match '%s'. "
                   "Try 'help help' or 'man -k %s' or 'info %s'.\n", str, str, str);
    }
}
