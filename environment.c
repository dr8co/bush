#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "main.h"

void environ_ment() {
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

void set_environment_variables() {
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
    left_right[0] = _strtok(args[1], "=");
    while ((left_right[n] = _strtok(NULL, "=")) != NULL)
        n++;
    left_right[n] = NULL;
    setenv(left_right[0], left_right[1], 0);
}

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
    cwd[0] = '\0';
    pid = 0;
    environ_flag = 0;
    bang_flag = 0;
}

void free_global_vars() {
    free(input_redirection_file);
    free(output_redirection_file);
    free(absolute_shell_name);
}
