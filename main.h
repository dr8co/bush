#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>

/*GLOBAL VARIABLES*/
extern int pipe_count, fd;
extern char *args[512];
extern char *history_file;
extern char input_buffer[1024];
extern int flag, len;
extern char cwd[1024], *home;
extern pid_t pid;
extern int no_of_lines;
extern int flag_pipe, flag_without_pipe;
extern int output_redirection, input_redirection;
extern int bang_flag;
extern int status;
extern char history_data[1024][1024];
extern char current_directory[1024];
extern char ret_file[3072];
extern char his_var[2048];
extern char *input_redirection_file;
extern char *output_redirection_file;
extern char **environ;
extern char *user, hostname[256];
extern int cmd_count;
extern char *prompt;

void clear_variables();

void file_process();

void file_write();

void execute_event();

void environ_ment();

void set_environment_variables();

void change_directory();

void print_working_dir();

void run_echo(char *echo_val);

void execute_history();

char *skip_whitespaces(char *s);

void tokenize_commands(char *com_exec);

void tokenize_redirect_input_output(char *cmdExec);

void tokenize_redirect_input(char *cmdExec);

void tokenize_redirect_output(char *cmdExec);

char *skip_quotes(const char *str);

int split(char *cmd_exec, int, int, int);

void execute_pipe();

int command(int, int, int, char *cmd_exec);

char *read_cmd(void);

void print_prompt1();

void print_prompt2();

int _atoi(const char *str);

int _strlen(const char *s);

char *_strcpy(char *dest, const char *src);

int _strcmp(const char *s1, const char *s2);

char *_strcat(char *dest, char *src);

char *_memset(char *s, char b, unsigned int n);

char *_strchr(char *s, char c);

char *_strdup(const char *str);

char *_strtok(char *str, const char *delim);

void *_realloc(void *ptr, unsigned int new_size);

char *_strstr(const char *haystack, const char *needle);

char *replace_str(const char *str, const char *old, const char *new);

char *strtok_skip(char *str, char *delim);

void sigintHandler(int sig_num);

void free_global_vars();

void init_shell();

#endif /* MAIN_H */
