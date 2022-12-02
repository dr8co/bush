/**
 * @file main.h
 * @author Ian Duncan (dr8co@duck.com)
 * @brief project header file
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MAIN_H
#define MAIN_H

#define PATH_MAX 4096 // Maximum length of a file path.

/* Global variables for this file */
extern char *args[512];
extern char input_buffer[1024];
extern char **environ;

/* Function Declarations */
void clear_variables();

void read_history();

void write_history();

void execute_event();

void print_env();

void set_environment_vars();

void change_directory();

void print_working_dir();

void run_echo(char *echo_val);

void print_history();

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

void signalHandler(int sig_num);

void free_global_vars();

void init_shell();

void free_histfile();

char *trim_leading_trailing(const char *str);

int is_numeric(const char *str);

#endif /* MAIN_H */
