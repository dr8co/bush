/**
 * @file tokenize.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for tokenization operations
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"
#include <unistd.h>

/* Global variables for this file */
char *input_redirection_file;
char *output_redirection_file;

/**
 * @brief tokenizes commands.
 * @param com_exec - the command to tokenize.
 */
void tokenize_commands(char *com_exec) {
    int m = 1;

    args[0] = str_tok(com_exec, " ");
    while ((args[m] = str_tok(NULL, " ")) != NULL) {
        args[m] = skip_whitespaces(args[m]);
        ++m;
    }
}

/**
 * @brief tokenize command for both input and output redirections.
 * @param cmdExec - the command to tokenize.
 */
void tokenize_redirect_input_output(char *cmdExec) {
    char *io_token[100];
    char *new_cmd_exec1;
    new_cmd_exec1 = str_dup(cmdExec);
    int m = 1;
    io_token[0] = str_tok(new_cmd_exec1, "<");
    while ((io_token[m] = str_tok(NULL, ">")) != NULL)
        ++m;
    io_token[1] = skip_whitespaces(io_token[1]);
    io_token[2] = skip_whitespaces(io_token[2]);
    input_redirection_file = str_dup(io_token[1]);
    output_redirection_file = str_dup(io_token[2]);
    tokenize_commands(io_token[0]);
}

/**
 * @brief tokenize command for input redirections.
 * @param cmdExec - the command to tokenize.
 */
void tokenize_redirect_input(char *cmdExec) {
    char *i_token[100];
    char *new_cmd_exec1;
    new_cmd_exec1 = str_dup(cmdExec);
    int m = 1;
    i_token[0] = str_tok(new_cmd_exec1, "<");
    while ((i_token[m] = str_tok(NULL, "<")) != NULL)
        ++m;
    i_token[1] = skip_whitespaces(i_token[1]);
    input_redirection_file = str_dup(i_token[1]);
    tokenize_commands(i_token[0]);
}

/**
 * @brief tokenize command for output redirections.
 * @param cmdExec - the command to tokenize.
 */
void tokenize_redirect_output(char *cmdExec) {
    char *o_token[100];
    char *new_cmd_exec1;
    new_cmd_exec1 = str_dup(cmdExec);
    int m = 1;
    o_token[0] = str_tok(new_cmd_exec1, ">");
    while ((o_token[m] = str_tok(NULL, ">")) != NULL)
        ++m;
    o_token[1] = skip_whitespaces(o_token[1]);
    output_redirection_file = str_dup(o_token[1]);
    tokenize_commands(o_token[0]);
}
