/**
 * @file history.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for manipulation of shell history
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
extern char *home;
extern int line_number;
char history_data[1024][1024];


/**
 * @brief process the shell history file.
 */
void read_history() {
    history_file = (char *) malloc(1024 * sizeof(char));
    str_cpy(history_file, home);
    str_cat(history_file, "/.burning_bush_history");
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
    free(history_file);
}

/**
 * @brief free history data.
 */
void free_histfile() {
    free(history_file);
}
