#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include "main.h"

static int command(int input, int first, int last, char *cmd_exec) {
    int my_pipe_fd[2], ret, input_fd, output_fd;
    ret = pipe(my_pipe_fd);
    if (ret == -1) {
        perror("pipe");
        return 1;
    }
    pid = fork();

    if (pid == 0) {
        if (first == 1 && last == 0 && input == 0) {
            dup2(my_pipe_fd[1], 1);
        } else if (first == 0 && last == 0 && input != 0) {
            dup2(input, 0);
            dup2(my_pipe_fd[1], 1);
        } else {
            dup2(input, 0);
        }
        if (strchr(cmd_exec, '<') && strchr(cmd_exec, '>')) {
            input_redirection = 1;
            output_redirection = 1;
            tokenize_redirect_input_output(cmd_exec);
        } else if (strchr(cmd_exec, '<')) {
            input_redirection = 1;
            tokenize_redirect_input(cmd_exec);
        } else if (strchr(cmd_exec, '>')) {
            output_redirection = 1;
            tokenize_redirect_output(cmd_exec);
        }
        if (output_redirection == 1) {
            output_fd = creat(output_redirection_file, 0644);
            if (output_fd < 0) {
                fprintf(stderr, "Failed to open %s for writing\n", output_redirection_file);
                return (EXIT_FAILURE);
            }
            dup2(output_fd, 1);
            close(output_fd);
            output_redirection = 0;
        }
        if (input_redirection == 1) {
            input_fd = open(input_redirection_file, O_RDONLY, 0);
            if (input_fd < 0) {
                fprintf(stderr, "Failed to open %s for reading\n", input_redirection_file);
                return (EXIT_FAILURE);
            }
            dup2(input_fd, 0);
            close(input_fd);
            input_redirection = 0;
        }
        if (strcmp(args[0], "export") == 0) {
            set_environment_variables();
            return 1;
        }
        if (strcmp(args[0], "echo") == 0) {
            echo_calling(cmd_exec);
        } else if (strcmp(args[0], "history") == 0) {
            history_execute_with_constants();
        } else if (execvp(args[0], args) < 0) printf("%s: command not found\n", args[0]);
        exit(0);
    } else {
        waitpid(pid, 0, 0);
    }

    if (last == 1)
        close(my_pipe_fd[0]);
    if (input != 0)
        close(input);
    close(my_pipe_fd[1]);
    return my_pipe_fd[0];

}

int split(char *cmd_exec, int input, int first, int last) {
    char *new_cmd_exec1;
    new_cmd_exec1 = strdup(cmd_exec);
    //else
    {
        int m = 1;
        args[0] = strtok(cmd_exec, " ");
        while ((args[m] = strtok(NULL, " ")) != NULL)
            m++;
        args[m] = NULL;
        if (args[0] != NULL) {

            if (strcmp(args[0], "exit") == 0)
                exit(0);
            if (strcmp(args[0], "echo") != 0) {
                cmd_exec = skip_comma(new_cmd_exec1);
                int m = 1;
                args[0] = strtok(cmd_exec, " ");
                while ((args[m] = strtok(NULL, " ")) != NULL)
                    m++;
                args[m] = NULL;

            }
            if (strcmp("cd", args[0]) == 0) {
                change_directory();
                return 1;
            } else if (strcmp("pwd", args[0]) == 0) {
                parent_directory();
                return 1;
            }

        }
    }
    return command(input, first, last, new_cmd_exec1);
}

char *skip_comma(char *str) {
    int i = 0, j = 0;
    char temp[1000];
    while (str[i++] != '\0') {
        if (str[i - 1] != '"')
            temp[j++] = str[i - 1];
    }
    temp[j] = '\0';
    str = strdup(temp);

    return str;
}

char *skip_whitespaces(char *s) {
    while (isspace(*s)) ++s;
    return s;
}