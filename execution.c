#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

void echo_calling(char *echo_val) {
    int i, index = 0;
    environ_flag = 0;
    char new_args[1024], env_val[1000], *str[10];
    str[0] = strtok(echo_val, " ");
    str[1] = strtok(NULL, "");
    _strcpy(env_val, args[1]);
    if (str[1] == NULL) {
        printf("\n");
        return;
    }
    if (strchr(str[1], '$')) {
        environ_flag = 1;
    }

    _memset(new_args, '\0', sizeof(new_args));
    i = 0;
    while (str[1][i] != '\0') {
        if (str[1][i] == '"') {
            index = 0;
            while (str[1][i] != '\0') {
                if (str[1][i] != '"') {
                    new_args[index] = str[1][i];
                    flag = 1;
                    index++;
                }
                i++;
            }
        } else if (str[1][i] == 39) {
            index = 0;
            while (str[1][i] != '\0') {
                if (str[1][i] != 39) {
                    new_args[index] = str[1][i];
                    flag = 1;
                    index++;
                }
                i++;
            }
        } else if (str[1][i] != '"') {
            new_args[index] = str[1][i];
            index++;
            i++;
        } else i++;
    }


    new_args[index] = '\0';
    if ((_strcmp(args[1], new_args) == 0) && (environ_flag == 0))
        printf("%s\n", new_args);
    else {
        _strcpy(args[1], new_args);
        if (environ_flag == 1) {
            environ_ment();
        } else if (environ_flag == 0) {
            printf("%s\n", new_args);
        }
    }
}

void history_execute_with_constants() {
    int num, i, start_index;
    if (bang_flag == 1) {
        for (i = 0; i < no_of_lines; i++)
            printf("%s\n", history_data[i]);
    } else if (args[1] == NULL) {
        for (i = 0; i < no_of_lines - 1; i++)
            printf("%s\n", history_data[i]);
        printf(" %d %s\n", no_of_lines, his_var);
    } else {
        if (args[1] != NULL)
            num = _atoi(args[1]);
        if (num > no_of_lines) {
            for (i = 0; i < no_of_lines - 1; i++)
                printf("%s\n", history_data[i]);
            printf(" %d %s\n", no_of_lines, his_var);
        }
        start_index = no_of_lines - num;
        for (i = start_index; i < no_of_lines - 1; i++)
            printf("%s\n", history_data[i]);
        printf(" %d %s\n", no_of_lines, his_var);
    }

}


void bang_execute() {
    char bang_val[1000];
    char *tokenize_bang[100], *num_ch[10];
    int i, n = 1, num, index = 0;
    i = 1;
    if (input_buffer[i] == '!') {
        _strcpy(bang_val, history_data[no_of_lines - 1]);
    } else if (input_buffer[i] == '-') {
        n = 1;
        num_ch[0] = strtok(input_buffer, "-");
        while ((num_ch[n] = strtok(NULL, "-")) != NULL)
            n++;
        num_ch[n] = NULL;
        num = _atoi(num_ch[1]);

        index = no_of_lines - num;
        _strcpy(bang_val, history_data[index]);

    } else {
        num_ch[0] = strtok(input_buffer, "!");
        num = _atoi(num_ch[0]);
        _strcpy(bang_val, history_data[num - 1]);
    }
    tokenize_bang[0] = strtok(bang_val, " ");
    while ((tokenize_bang[n] = strtok(NULL, "")) != NULL)
        n++;
    tokenize_bang[n] = NULL;
    _strcpy(bang_val, tokenize_bang[1]);
    printf("%s\n", bang_val);
    _strcpy(input_buffer, bang_val);

}

int command(int input, int first, int last, char *cmdExec) {
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
        if (strchr(cmdExec, '<') && strchr(cmdExec, '>')) {
            input_redirection = 1;
            output_redirection = 1;
            tokenize_redirect_input_output(cmdExec);
        } else if (strchr(cmdExec, '<')) {
            input_redirection = 1;
            tokenize_redirect_input(cmdExec);
        } else if (strchr(cmdExec, '>')) {
            output_redirection = 1;
            tokenize_redirect_output(cmdExec);
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
        if (_strcmp(args[0], "export") == 0) {
            set_environment_variables();
            return 1;
        }
        if (_strcmp(args[0], "echo") == 0) {
            echo_calling(cmdExec);
        } else if (_strcmp(args[0], "history") == 0) {
            history_execute_with_constants();
        } else if (execvp(args[0], args) < 0) {
            printf("%s: %i: %s: not found\n", absolute_shell_name, cmd_count, args[0]);

        }
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

void execute_pipe() {

    int i, n = 1, input, first;

    input = 0;
    first = 1;

    cmd_exec[0] = strtok(input_buffer, "|");

    while ((cmd_exec[n] = strtok(NULL, "|")) != NULL)
        n++;
    cmd_exec[n] = NULL;
    pipe_count = n - 1;
    for (i = 0; i < n - 1; i++) {
        input = split(cmd_exec[i], input, first, 0);
        first = 0;
    }
    input = split(cmd_exec[i], input, first, 1);
    input = 0;
}
