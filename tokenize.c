#include <stdlib.h>
#include "main.h"

void tokenize_commands(char *com_exec) {
    int m = 1;
    args[0] = _strtok(com_exec, " ");
    while ((args[m] = _strtok(NULL, " ")) != NULL)
        m++;
}

void tokenize_redirect_input_output(char *cmdExec) {
    char *io_token[100];
    char *new_cmd_exec1;
    new_cmd_exec1 = _strdup(cmdExec);
    int m = 1;
    io_token[0] = _strtok(new_cmd_exec1, "<");
    free(new_cmd_exec1);
    while ((io_token[m] = _strtok(NULL, ">")) != NULL)
        m++;
    io_token[1] = skip_whitespaces(io_token[1]);
    io_token[2] = skip_whitespaces(io_token[2]);
    input_redirection_file = _strdup(io_token[1]);
    output_redirection_file = _strdup(io_token[2]);
    tokenize_commands(io_token[0]);
}

void tokenize_redirect_input(char *cmdExec) {
    char *i_token[100];
    char *new_cmd_exec1;
    new_cmd_exec1 = _strdup(cmdExec);
    int m = 1;
    i_token[0] = _strtok(new_cmd_exec1, "<");
    while ((i_token[m] = _strtok(NULL, "<")) != NULL)
        m++;
    i_token[1] = skip_whitespaces(i_token[1]);
    input_redirection_file = _strdup(i_token[1]);
    tokenize_commands(i_token[0]);
    free(new_cmd_exec1);
}

void tokenize_redirect_output(char *cmdExec) {
    char *o_token[100];
    char *new_cmd_exec1;
    new_cmd_exec1 = _strdup(cmdExec);
    int m = 1;
    o_token[0] = _strtok(new_cmd_exec1, ">");
    free(new_cmd_exec1);
    while ((o_token[m] = _strtok(NULL, ">")) != NULL)
        m++;
    o_token[1] = skip_whitespaces(o_token[1]);
    output_redirection_file = _strdup(o_token[1]);
    tokenize_commands(o_token[0]);
}
