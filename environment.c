#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

/* Global vars */
char *user, hostname[256], cwd[1024];
char *home, *prompt;

/**
 * @brief prints the environment variables.
 */
void print_env() {
    int i = 1, index = 0;
    char env_val[1000], *value;
    while (args[1][i] != '\0') {
        env_val[index] = args[1][i];
        index++;
        i++;
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
        for (env = environ; *env != 0; env++) {
            char *value = *env;
            printf("export %s\n", value);
        }
        return;
    }
    left_right[0] = strtok_skip(args[1], "=");
    while ((left_right[n] = strtok_skip(NULL, "=")) != NULL)
        n++;
    left_right[n] = NULL;
    setenv(left_right[0], left_right[1], 0);
}

/**
 * @brief clears the global variables.
 */
void clear_variables() {
    fd = 0;
    flag = 0;
    len = 0;
    no_of_lines = 0;
    pipe_count = 0;
    flag_pipe = 0;
    flag_without_pipe = 0;
    output_redirection = 0;
    input_redirection = 0;
    input_buffer[0] = '\0';
    pid = 0;
    bang_flag = 0;
}

/**
 * @brief frees the global variables that were dynamically allocated to the memory.
 */
void free_global_vars() {
    free(input_redirection_file);
    free(output_redirection_file);
    free(prompt);
}

/**
 * @brief initializes the shell.
 */
void init_shell() {
    user = getenv("USER");
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));
    home = getenv("HOME");
    if (home == NULL) {
        home = "/home";
    }
    prompt = replace_str(cwd, home, "~");
}
