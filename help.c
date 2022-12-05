/**
 * @file help.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for help-related functions.
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include "main.h"

/* Help Messages */
extern char *cd_msg;
extern char *echo_msg;
extern char *exit_msg;
extern char *help_msg;

/**
 * @brief Prints help message to stdout.
 * @param str the command whose help message is printed.
 */
void find_help(const char *str){
    if (str == NULL)
        printf("%s\n",help_msg);
    else {
        if (str_cmp(str, "cd") == 0)
            printf("%s\n",cd_msg);
        else if (str_cmp(str, "echo") == 0)
            printf("%s\n",echo_msg);
        else if (str_cmp(str, "exit") == 0)
            printf("%s\n",exit_msg);
        else
            printf("%s\n",help_msg);
    }
}
