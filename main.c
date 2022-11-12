#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

/*GLOBAL VARIABLES*/
int pipe_count = 0, fd;
static char *args[512];
char *history_file;
char input_buffer[1024];
char *cmd_exec[100];
int flag, len;
char cwd[1024];
int flag_pipe = 1;
pid_t pid;
int no_of_lines;
int environ_flag;
int flag_pipe, flag_without_pipe, output_redirection, input_redirection;
int bang_flag;
int pid, status;
char history_data[1000][1000];
char current_directory[1000];
char ret_file[3000];
char his_var[2000];
char *input_redirection_file;
char *output_redirection_file;

int main() {
    int status;
    char ch[2] = {"\n"};
    getcwd(current_directory, sizeof(current_directory));
    signal(SIGINT, sigintHandler);
    while (1) {
        clear_variables();
        prompt();
        fgets(input_buffer, 1024, stdin);
        if (strcmp(input_buffer, ch) == 0) {
            continue;
        }
        if (input_buffer[0] != '!') {
            file_process();
            file_write();
        }
        len = strlen(input_buffer);
        input_buffer[len - 1] = '\0';
        strcpy(his_var, input_buffer);
        if (strcmp(input_buffer, "exit") == 0) {
            flag = 1;
            break;
        }
        if (input_buffer[0] == '!') {
            file_process();
            bang_flag = 1;
            bang_execute();
        }
        execute_pipe();
        waitpid(pid, &status, 0);

    }
    if (flag == 1) {
        exit(0);
        return 0;
    }
    return 0;
}