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


int main(__attribute__((unused)) int argc, char **argv) {
    char ch[2] = {"\n"};
    shell_name = _strdup(argv[0]);
    getcwd(current_directory, sizeof(current_directory));
    absolute_shell_name = abs_name();
    signal(SIGINT, sigintHandler);

    while (1) {
        clear_variables();
        print_prompt1();
        char *cmd = read_cmd();

        if (cmd) {
            ++cmd_count;
        } else {
            exit(0);
        }
        _strcpy(input_buffer, cmd);
        free(cmd);

        if (_strcmp(input_buffer, ch) == 0 || input_buffer[0] == '#')
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
            bang_execute();
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
