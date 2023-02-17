/**
 * @file prompt.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for printing shell prompts
 * @version 3.0
 * @date 2023-02-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"
#include <stdio.h>

/* Global variables for this file */
extern char *user, hostname[256];
extern char *prompt;

/**
 * @brief prints the regular prompt string.
 */
void print_prompt1() {
    if (user && prompt && *hostname) {
        printf("\033[1;34m");
        printf("%s@%s", user, hostname);

        printf("\033[0m");
        printf(":");

        printf("\033[1;35m");
        printf("%s", prompt);

        printf("\033[0m");
        printf("$ ");

    } else {
        printf("$ ");
    }
}

/**
 * @brief prints the secondary prompt.
 */
void print_prompt2() {
    printf("> ");
}
