#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>

/*GLOBAL VARIABLES*/
extern int pipe_count, fd;
static char *args[512];
extern char *history_file;
extern char input_buffer[1024];
extern char *cmd_exec[100];
extern int flag, len;
extern char cwd[1024];
extern pid_t pid;
extern int no_of_lines;
extern int environ_flag;
extern int flag_pipe, flag_without_pipe, output_redirection, input_redirection;
extern int bang_flag;
extern int pid, status;
extern char history_data[1000][1000];
extern char current_directory[1000];
extern char ret_file[3000];
extern char his_var[2000];
extern char *input_redirection_file;
extern char *output_redirection_file;
extern char **environ;


void clear_variables();

void file_process();

void file_write();

void bang_execute();

void environ_ment();

void set_environment_variables();

void change_directory();

void parent_directory();

void echo_calling(char *echo_val);

void history_execute_with_constants();

char *skip_whitespaces(char *s);

void tokenize_commands(char *com_exec);

void tokenize_redirect_input_output(char *cmd_exec);

void tokenize_redirect_input(char *cmd_exec);

void tokenize_redirect_output(char *cmd_exec);

char *skip_comma(char *str);

int split(char *cmd_exec, int, int, int);

void execute_pipe();

static int command(int, int, int, char *cmd_exec);

void prompt();

void sigintHandler(__attribute__((unused)) int sig_num);

#endif /* MAIN_H */