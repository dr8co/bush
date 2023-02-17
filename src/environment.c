/**
 * @file environment.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for manipulating shell environment.
 * @version 3.0
 * @date 2023-02-18
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "main.h"


/* Global variables for this file */
extern int fd, line_number, event_flag;
extern pid_t pid;
extern int output_redirection, input_redirection;
extern char *input_redirection_file;
extern char *output_redirection_file;
extern char *prompt;
int element = 0;


/**
 * @brief prints the environment variables.
 */
void print_env() {
    int i = 1, index = 0;
    char env_val[1000], *value;
    while (args[1][i] != '\0') {
        env_val[index] = args[1][i];
        ++index;
        ++i;
    }
    env_val[index] = '\0';
    value = getenv(env_val);

    if (!value)
        printf("\n");
    else printf("%s\n", value);
}

/**
 * @brief sets environment variables.
 */
void set_environment_vars() {
    int n = 1;
    char *left_right[100];
    if (args[1] == NULL) {
        char **env;
        for (env = environ; *env != 0; ++env) {
            char *value = *env;
            printf("export %s\n", value);
        }
        return;
    }
    left_right[0] = str_tok(args[1], "=");
    while ((left_right[n] = str_tok(NULL, "=")) != NULL)
        ++n;
    left_right[n] = NULL;
    setenv(left_right[0], left_right[1], 0);
}

/**
 * @brief clears the global variables.
 */
void clear_variables() {
    fd = 0;
    line_number = 0;
    output_redirection = 0;
    input_redirection = 0;
    input_buffer[0] = '\0';
    pid = 0;
    event_flag = 0;

    for (; args[element]; ++element) {
        args[element] = NULL;
    }
}

/**
 * @brief frees the global variables that were dynamically allocated to the memory.
 */
void free_global_vars() {
    free(input_redirection_file);
    free(output_redirection_file);
    free(prompt);
}

