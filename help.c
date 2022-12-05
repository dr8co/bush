/**
 * @file help.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for help-related functions.
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/* Help Messages */
extern char *cd_msg;
extern char *echo_msg;
extern char *exit_msg;
extern char *help_msg;

/**
 * @brief Reads the content of a text file.
 * @param filename the name of the file to be read.
 * @param filesize the size of the file (modified in-place).
 * @return the file content as a character array.
 */
char *readfile(const char *filename, size_t *filesize) {
    /* Ensure that filesize will be set to 0 if the function
     * returns NULL due to an error.
     */
    if (filesize == NULL)
        return NULL;
    *filesize = 0;

    if (filename == NULL)
        return NULL;

    int fdes = open(filename, O_RDONLY);
    if (fdes == -1) {
        perror("open");
        return NULL;
    }

    // Get file size (and other information)
    struct stat result;
    if (fstat(fdes, &result) == -1) {
        perror("stat");
        close(fdes);
        return NULL;
    }

    // Make sure the file is a regular file.
    if (!S_ISREG(result.st_mode)) {
        fprintf(stderr, "Not a file: %s\n", filename);
        close(fdes);
        return NULL;
    }

    // Get the size of the file
    off_t size = result.st_size;
    *filesize = (size_t) size;

    // Check if the file has any data.
    if (size == 0) {
        close(fdes);
        return NULL;
    }

    // Try to allocate space to store file.
    char *file_content = (char *) malloc(sizeof(char) * size);
    if (file_content == NULL) {
        fprintf(stderr, "Failed to alloc memory.\n");
        close(fdes);
        return NULL;
    }

    // Try to read the file.
    if (read(fdes, file_content, size) < (ssize_t) size) {
        perror("read");
        fprintf(stderr, "Content read is less than expected due to the problem above.\n");

        free(file_content);
        close(fdes);
        return NULL;
    }

    // See if there is more to read than we expected.
    if (read(fdes, file_content, 1) == 1) {
        fprintf(stderr, "File increased in size unexpectedly.\n");
        free(file_content);
        close(fdes);
        return NULL;
    }

    if (close(fdes) != 0)
        perror("close");

    return file_content;
}

/**
 * @brief prints the content of a file.
 * @param filename the file to process.
 */
void print_file(const char *filename) {
    size_t size;
    char *bytes = readfile(filename, &size);
    if (bytes) {
        fwrite(bytes, 1, size, stdout);
        free(bytes);
    }
}

/**
 * @brief Prints help message to stdout.
 * @param str the command whose help message is printed.
 */
void find_help(const char *str){
    if (str == NULL)
        printf("%s\n",help_msg);
    else {
        if (str_cmp(str, "cd") == 0)
            printf("%s\n",cd_msg);
        else if (str_cmp(str, "echo") == 0)
            printf("%s\n",echo_msg);
        else if (str_cmp(str, "exit") == 0)
            printf("%s\n",exit_msg);
        else
            printf("%s\n",help_msg);
    }
}
