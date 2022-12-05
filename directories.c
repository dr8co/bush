/**
 * @file directories.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for directory-related functions
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

/* Global variables for this file */
char *user = NULL, hostname[256], cwd[PATH_MAX];
char *home = NULL, *prompt = NULL;
extern int cmd_count;

/**
 * @brief Changes the shell working directory.
 * @return 0 if directory is changed, -1 otherwise.
 */
int change_directory() {
    char *old_dir = getenv("OLDPWD");

    // Handle 'cd', 'cd ~' and 'cd ~/' commands to change working directory to home directory.
    if ((args[1] == NULL) || (str_cmp(args[1], "~") == 0) || (str_cmp(args[1], "~/") == 0)) {
        if (chdir(home) == 0) {
            setenv("OLDPWD", cwd, 1);
            setenv("PWD", home, 1);
            getcwd(cwd, sizeof(cwd));

            // Update the prompt.
            free(prompt);
            prompt = replace_str(cwd, home, "~");
            return 0;
        }
    }
        // Handle 'cd -' command to change the working directory to the previous directory.
    else if (str_cmp(args[1], "-") == 0) {
        if (old_dir != NULL) {

            // change working dir to previous directory if exists.
            if (chdir(old_dir) == 0) {
                setenv("PWD", old_dir, 1);
                setenv("OLDPWD", cwd, 1);
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", old_dir);

                // Update the prompt.
                free(prompt);
                prompt = replace_str(cwd, home, "~");
                return 0;
            }
        }
            // change shell working directory to home directory if the old directory does not exist.
        else {
            if (chdir(home) == 0) {
                setenv("PWD", home, 1);
                setenv("OLDPWD", cwd, 1);
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", home);

                // Update the prompt.
                free(prompt);
                prompt = replace_str(cwd, home, "~");
                return 0;
            }
        }
    }
        // Handle 'cd .' command.
    else if (str_cmp(args[1], ".") == 0) {
        setenv("OLDPWD", cwd, 1);
        setenv("PWD", cwd, 1);
        return 0;
    } else {
        // The directory was not found.
        if (chdir(args[1]) < 0) {
            printf("burning bush: %i: cd: no such file or directory: %s\n", cmd_count, args[1]);
            return -1;
        }
            // Change working directory to the specified directory in the argument of the 'cd' command.
        else {
            char new_dir[PATH_MAX];
            getcwd(new_dir, sizeof(new_dir));
            setenv("OLDPWD", cwd, 1);
            setenv("PWD", new_dir, 1);
            getcwd(cwd, sizeof(cwd));

            // Update the prompt.
            free(prompt);
            prompt = replace_str(cwd, home, "~");
            return 0;
        }
    }
}

/**
 * @brief prints the working directory.
 */
void print_working_dir() {
    if (*cwd) {
        printf("%s\n", cwd);
    } else
        perror("error in reading current directory");
}

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
    getcwd(cwd, sizeof(cwd));
    if (!home) {
        home = getenv("HOME");
        if (!home)
            home = "/home";
    }
    prompt = replace_str(cwd, home, "~");
}
