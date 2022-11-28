#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"

/*GLOBAL VARIABLES*/
int pipe_count = 0, fd;
char *args[512];
char *history_file;
char input_buffer[1024];
int flag = 0, len;
int flag_pipe = 1;
pid_t pid;
int no_of_lines;
int flag_without_pipe;
int output_redirection, input_redirection;
int bang_flag;
int status;//pid, status;
char history_data[1024][1024];
char ret_file[3072];
char his_var[2048];
char *input_redirection_file;
char *output_redirection_file;
int cmd_count = 0;

/**
 * @brief the shell entry point.
 * @param argc - argument count.
 * @param argv - argument vector.
 * @return always 0.
 */
int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
    char *cmd = NULL, *cmd2 = NULL;

    init_shell();
    signal(SIGINT, signalHandler);

    while (1) {
        clear_variables();
        print_prompt1();
        cmd = read_cmd();

        if (cmd) {
            ++cmd_count;
            cmd2 = trim_leading_trailing(cmd);
        } else {
            exit(0);
        }
        _strcpy(input_buffer, cmd2);
        free(cmd);
        free(cmd2);

        if (_strcmp(input_buffer, "\n") == 0 || input_buffer[0] == '#')
            continue;

        if (input_buffer[0] != '!') {
            file_process();
            file_write();
        }
        len = _strlen(input_buffer);
        input_buffer[len - 1] = '\0';
        _strcpy(his_var, input_buffer);

        if (_strcmp(input_buffer, "exit") == 0 || _strcmp(input_buffer, "exit\n") == 0) {
            flag = 1;
            break;
        }

        if (input_buffer[0] == '!') {
            file_process();
            free(history_file);
            bang_flag = 1;
            execute_event();
        }
        execute_pipe();
        waitpid(pid, &status, 0);
    }

    free_global_vars();

    if (flag == 1) {
        exit(0);
    }
    return 0;
}
