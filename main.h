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

#include <stddef.h>

/* Global variables for the entire project */
extern char *args[512];
extern char input_buffer[1024];
extern char **environ;

/******* Function Declarations *******/

/* strings_1.c */
char *str_str(const char *haystack, const char *needle);
char *str_tok(char *str, const char *delim);
char *str_cpy(char *dest, const char *src);
int str_cmp(const char *s1, const char *s2);
char *str_cat(char *dest, char *src);
char *str_chr(char *s, char c);
char *str_dup(const char *str);
int str_len(const char *s);

/* strings_2.c */
char *replace_str(const char *str, const char *old, const char *new);
char *trim_leading_trailing(const char *str);
char *strtok_skip(char *str, char *delim);
char *skip_quotes(const char *str);
char *skip_whitespaces(char *s);

/* process_cmd.c */
void tokenize_redirect_input_output(char *cmdExec);
void tokenize_redirect_output(char *cmdExec);
void tokenize_redirect_input(char *cmdExec);
int split(char *cmd_exec, int, int, int);
void tokenize_commands(char *com_exec);

/* environment.c */
void set_environment_vars();
void free_global_vars();
void clear_variables();
void print_env();

/* execution.c */
int command(int, int, int, char *cmd_exec);
void run_echo(char *echo_val);
void execute_event();
void execute_pipe();

/* history.c */
void write_history();
void print_history();
void free_histfile();
void read_history();

/* memory.c */
void *re_alloc(void *ptr, unsigned int new_size);
char *mem_set(char *s, char b, unsigned int n);

/* fileops.c */
char *readfile(const char *filename, size_t *filesize);
void print_file(const char *filename);

/* directories.c */
void print_working_dir();
int change_directory();

/* numbers.c */
int is_numeric(const char *str);
int atoi_(const char *str);

/* get_info.c */
char *read_cmd(void);
void init_shell();

/* prompt.c */
void print_prompt1();
void print_prompt2();

/* help.c */
void find_help(const char *str);

/* signal_handler.c */
void signalHandler(int sig_num);

#endif /* MAIN_H */
