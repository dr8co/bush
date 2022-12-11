/**
 * @file history.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for manipulation of shell history.
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* Global variables for this file */
int fd;
char *history_file;
extern char *home, his_var[HIST_MAX * 2];
extern int line_number, event_flag;
char history_data[HIST_MAX][HIST_MAX];


/**
 * @brief process the shell history file.
 */
void read_history() {
    fd = open(history_file, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    int bytes_read, i, x = 0, index = 0;
    char buffer[1], temp_data[1024];
    do {
        bytes_read = (int) read(fd, buffer, sizeof(buffer));
        for (i = 0; i < bytes_read; ++i) {
            temp_data[index] = buffer[i];
            ++index;
            if (buffer[i] == '\n') {
                temp_data[index - 1] = '\0';
                ++line_number;
                index = 0;
                str_cpy(history_data[x], temp_data);
                ++x;
                temp_data[0] = '\0';
            }
        }
    } while (bytes_read == sizeof(buffer));
    close(fd);
}

/**
 * @brief record history of the shell in the history file.
 */
void write_history() {

    int fd_out, ret_write, len;
    char input_data[2048];
    line_number++;
    char no[10];
    sprintf(no, "%d", line_number);
    str_cpy(input_data, " ");
    str_cat(input_data, no);
    str_cat(input_data, " ");
    str_cat(input_data, input_buffer);

    len = str_len(input_data);
    fd_out = open(history_file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    ret_write = (int) write(fd_out, input_data, len);
    if (ret_write < 0) {
        printf("Error in recording history.\n");
        return;
    }
    close(fd_out);
}

/**
 * @brief print the history of shell commands.
 */
void print_history() {
    if (args[1]) {
        if (str_cmp(args[1], "-c") == 0) {
            delete_histfile();
            return;
        }
    }

    int num = 0, i, start_index;

    if (event_flag == 1) {
        for (i = 0; i < line_number; ++i)
            printf("%s\n", history_data[i]);
    } else if (args[1] == NULL) {
        for (i = 0; i < line_number - 1; ++i)
            printf("%s\n", history_data[i]);
        printf(" %d %s\n", line_number, his_var);
    } else {
        if (args[1] != NULL)
            num = atoi_(args[1]);
        if (num > line_number) {
            for (i = 0; i < line_number - 1; ++i)
                printf("%s\n", history_data[i]);
            printf(" %d %s\n", line_number, his_var);
        }
        start_index = line_number - num;
        for (i = start_index; i < line_number - 1; ++i)
            printf("%s\n", history_data[i]);
        printf(" %d %s\n", line_number, his_var);
    }

}

/**
 * @brief free history data.
 */
void free_histfile() {
    free(history_file);
}

/**
 * @brief Checks if the history file has reached its limit.
 * @return 1 if history file is full, 0 otherwise.
 */
int is_histfile_full() {
    int file, r, line = 0;
    char b[1];

    history_file = (char *) malloc(1024 * sizeof(char));
    str_cpy(history_file, home);
    str_cat(history_file, "/.burning_bush_history");

    file = open(history_file, O_RDONLY, S_IRUSR);

    if (file < 0) {
        close(file);
        return 0;
    }

    do {
        r = (int) read(file, b, sizeof(b));
        for (int i = 0; i < r; ++i) {
            if (b[i] == '\n') {
                ++line;
            }
        }
    } while (r == sizeof(b));

    if (line >= HIST_MAX - 2) {
        close(file);
        return 1;
    }
    close(file);

    return 0;
}

/**
 * @brief Deletes shell command history.
 */
void delete_histfile() {
    if (unlink(history_file) < 0) {
        printf("Maximum history record reached. Please delete history file\n");
        printf("at %s to avoid unnecessary errors/bugs.\n", history_file);
    }
}
