/**
 * @file execution.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for functions that handle execution of commands.
 * @version 2.1
 * @date 2023-01-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

/* Global variables for this file */
pid_t pid;
int line_number;
int output_redirection, input_redirection;
extern int cmd_count;
extern char history_data[HIST_MAX][HIST_MAX];
extern char his_var[HIST_MAX * 2];
extern char *input_redirection_file;
extern char *output_redirection_file;


/**
 * @brief execute the 'echo' command.
 * @param echo_val - the argument(s) of the 'echo' command.
 */
void run_echo(char *echo_val) {
    int i, index = 0;
    int environ_flag = 0;
    char new_args[1024], env_val[1000], *str[10];
    str[0] = str_tok(echo_val, " ");
    str[1] = str_tok(NULL, "");
    str_cpy(env_val, args[1]);
    if (str[1] == NULL) {
        printf("\n");
        return;
    }
    if (str_chr(str[1], '$')) {
        environ_flag = 1;
    }

    mem_set(new_args, '\0', sizeof(new_args));
    i = 0;
    while (str[1][i] != '\0') {
        if (str[1][i] == '"') {
            index = 0;
            while (str[1][i] != '\0') {
                if (str[1][i] != '"') {
                    new_args[index] = str[1][i];
                    ++index;
                }
                ++i;
            }
        } else if (str[1][i] == 39) {
            index = 0;
            while (str[1][i] != '\0') {
                if (str[1][i] != 39) {
                    new_args[index] = str[1][i];
                    ++index;
                }
                ++i;
            }
        } else if (str[1][i] != '"') {
            new_args[index] = str[1][i];
            ++index;
            ++i;
        } else ++i;
    }

    new_args[index] = '\0';
    if ((str_cmp(args[1], new_args) == 0) && (environ_flag == 0))
        printf("%s\n", new_args);
    else {
        str_cpy(args[1], new_args);
        if (environ_flag) {
            print_env();
        } else {
            printf("%s\n", new_args);
        }
    }
}

/**
 * @brief execute events in the shell commands history.
 */
void execute_event() {
    char event_val[1000];
    char *event_token[100], *num_ch[10];
    int i = 1, n = 1, num, index = 0;

    if (input_buffer[i] == '!') {
        str_cpy(event_val, history_data[line_number - 1]);
    } else if (input_buffer[i] == '-') {
        n = 1;
        num_ch[0] = str_tok(input_buffer, "-");
        while ((num_ch[n] = str_tok(NULL, "-")) != NULL)
            ++n;
        num_ch[n] = NULL;
        num = atoi_(num_ch[1]);

        index = line_number - num;
        str_cpy(event_val, history_data[index]);

    } else {
        num_ch[0] = str_tok(input_buffer, "!");
        num = atoi_(num_ch[0]);
        str_cpy(event_val, history_data[num - 1]);
    }
    event_token[0] = str_tok(event_val, " ");
    while ((event_token[n] = str_tok(NULL, "")) != NULL)
        n++;
    event_token[n] = NULL;
    str_cpy(event_val, event_token[1]);
    printf("%s\n", event_val);
    str_cpy(input_buffer, event_val);
}

/**
 * @brief execute commands.
 * @param input - the input.
 * @param first - first piped command.
 * @param last - last piped command.
 * @param cmdExec - the command to be executed.
 * @return 1 (SUCCESS), 0 (FAILURE).
 */
int command(int input, int first, int last, char *cmdExec) {
    int pipedes[2], ret, input_fd, output_fd;

    ret = pipe(pipedes);
    if (ret == -1) {
        perror("pipe error");
        return 1;
    }
    pid = fork();

    if (pid == 0) {
        if (first == 1 && last == 0 && input == 0) {
            dup2(pipedes[1], 1);
        } else if (first == 0 && last == 0 && input != 0) {
            dup2(input, 0);
            dup2(pipedes[1], 1);
        } else {
            dup2(input, 0);
        }
        if (str_chr(cmdExec, '<') && str_chr(cmdExec, '>')) {
            input_redirection = 1;
            output_redirection = 1;
            tokenize_redirect_input_output(cmdExec);
        } else if (str_chr(cmdExec, '<')) {
            input_redirection = 1;
            tokenize_redirect_input(cmdExec);
        } else if (str_chr(cmdExec, '>')) {
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
        if (str_cmp(args[0], "export") == 0) {
            set_environment_vars();
            return 1;
        }
        if (str_cmp(args[0], "echo") == 0) {
            run_echo(cmdExec);
        } else if (str_cmp(args[0], "history") == 0) {
            print_history();
        } else if (execvp(args[0], args) < 0) {
            printf("The burning bush: %i: command not found: %s\n", cmd_count, args[0]);
        }
        exit(0);
    } else {
        waitpid(pid, 0, 0);
    }

    if (last == 1)
        close(pipedes[0]);
    if (input != 0)
        close(input);
    close(pipedes[1]);
    return pipedes[0];
}

/**
 * @brief execute piped commands.
 */
void execute_pipe() {
    char *cmd_exec[100];
    int i, n = 1, input, first;

    input = 0;
    first = 1;

    cmd_exec[0] = str_tok(input_buffer, "|");
    cmd_exec[0] = trim_leading_trailing(cmd_exec[0]);

    while ((cmd_exec[n] = str_tok(NULL, "|")) != NULL) {
        cmd_exec[n] = trim_leading_trailing(cmd_exec[n]);
        ++n;
    }
    cmd_exec[n] = NULL;

    for (i = 0; i < n - 1; ++i) {
        input = split(cmd_exec[i], input, first, 0);
        first = 0;
    }
    split(cmd_exec[i], input, first, 1);
    for (int j = 0; j <= n; ++j) {
        free(cmd_exec[j]);
    }
}
