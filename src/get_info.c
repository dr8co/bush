/**
 * @file get_info.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for functions to extract information.
 * @version 1.0
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

char *user = NULL, hostname[256], cwd[PATH_MAX];
char *home = NULL, *prompt = NULL, *ret_dir;

/**
 * @brief Gets the username (and home directory) of the current user.
 */
void get_username() {
    register struct passwd *pw;
    register uid_t uid;

    uid = geteuid();
    pw = getpwuid(uid);
    if (pw) {
        user = pw->pw_name;
        home = pw->pw_dir;
        if (!user) {
            user = getenv("USER");
            if (!user) {
                user = getenv("USERNAME");
                if (!user) {
                    user = "iam_who_iam";
                }
            }
        }
    } else { // If getpwuid() errored or returned NULL
        user = getenv("USER");
        if (!user) {
            user = getenv("USERNAME");
            if (!user) {
                user = "iam_who_iam";
            }
        }
    }
}

/**
 * @brief Gets the machine hostname.
 */
void get_hostname() {
    *hostname = '\0';
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        str_cpy(hostname, getenv("HOSTNAME"));
        if (*hostname == '\0')
            str_cpy(hostname, "Only_God_knows");
    }
}

/**
 * @brief initializes the shell.
 */
void init_shell() {
    get_username();
    get_hostname();
    ret_dir = getcwd(cwd, sizeof(cwd));
    if (!home) {
        home = getenv("HOME");
        if (!home)
            home = "/home";
    }
    prompt = replace_str(cwd, home, "~");
    // Empty history if full
    if (is_histfile_full())
        delete_histfile();
}

/**
 * @brief read commands from user input.
 * @return the commands entered, as a string.
 */
char *read_cmd(void) {
    char buff[1024];
    char *ptr = NULL;
    char ptr_len = 0;

    while (fgets(buff, 1024, stdin) != NULL) {
        int buff_len = str_len(buff);

        if (!ptr) {
            ptr = (char *) malloc(sizeof(buff) + 2);
        } else {
            char *ptr2 = re_alloc(ptr, ptr_len + buff_len + 1);

            if (ptr2) {
                ptr = ptr2;

            } else {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr) {
            perror("error: failed to alloc buffer");
            return NULL;
        }

        str_cpy(ptr + ptr_len, buff);

        if (buff[buff_len - 1] == '\n') {

            if (buff_len == 1 || buff[buff_len - 2] != '\\') {
                return ptr;
            }

            ptr[ptr_len + buff_len - 2] = '\0';
            buff_len -= 2;
            print_prompt2();
        }

        ptr_len += buff_len;
    }
    if (ptr == NULL) {
        printf("\n");
        exit(0);
    }

    return ptr;
}
