#include "main.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief process the shell history file.
 */
void read_history() {
    history_file = (char *) malloc(1024 * sizeof(char));
    _strcpy(history_file, home);
    _strcat(history_file, "/.burning_bush_history");
    fd = open(history_file, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    int bytes_read, i, x = 0, index = 0;
    char buffer[1], temp_data[1000];
    do {
        bytes_read = read(fd, buffer, sizeof(buffer));
        for (i = 0; i < bytes_read; ++i) {
            temp_data[index] = buffer[i];
            index++;
            if (buffer[i] == '\n') {
                temp_data[index - 1] = '\0';
                line_number++;
                index = 0;
                _strcpy(history_data[x], temp_data);
                x++;
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

    int fd_out, ret_write, str_len = 0;
    char input_data[2048];
    line_number++;
    char no[10];
    sprintf(no, "%d", line_number);
    _strcpy(input_data, " ");
    _strcat(input_data, no);
    _strcat(input_data, " ");
    _strcat(input_data, input_buffer);

    str_len = _strlen(input_data);
    fd_out = open(history_file, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    len = _strlen(input_buffer);
    ret_write = write(fd_out, input_data, str_len);
    if (ret_write < 0) {
        printf("Error in writing file\n");
        return;
    }
    close(fd_out);
    free(history_file);

}