#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/* Global Variables */
char *shell_name;
char *absolute_shell_name;
char current_directory[1024];
char cwd[1024];

/**
 * change_directory - Change the shell working directory.
 */
void change_directory() {
    char *home_dir = getenv("HOME");
    char *old_dir = getenv("OLDPWD");
    char cur_dir[1024];

    getcwd(cur_dir, sizeof(cur_dir));

    if (home_dir == NULL) {
        home_dir = "/home";
    }

    // Handle 'cd', 'cd ~' and 'cd ~/' commands to change working directory to home directory.
    if ((args[1] == NULL) || (_strcmp(args[1], "~") == 0) || (_strcmp(args[1], "~/") == 0)) {
        if (chdir(home_dir) == 0) {
            setenv("OLDPWD", cur_dir, 1);
            setenv("PWD", home_dir, 1);
        }
    }
    // Handle 'cd -' command to change the working directory to the previous directory.
    else if (_strcmp(args[1], "-") == 0) {
        if (old_dir != NULL) {

            // change working dir to previous directory if exists.
            if (chdir(old_dir) == 0) {
                setenv("PWD", old_dir, 1);
                setenv("OLDPWD", cur_dir, 1);
                printf("%s\n", old_dir);
            }
        }
        // change shell working directory to home directory if the old directory does not exist.
        else {
            if (chdir(home_dir) == 0) {
                setenv("PWD", home_dir, 1);
                setenv("OLDPWD", cur_dir, 1);
                printf("%s\n", home_dir);
            }

        }
    }
    // Handle 'cd .' command.
    else if (_strcmp(args[1], ".") == 0) {
        setenv("OLDPWD", cur_dir, 1);
        setenv("PWD", cur_dir, 1);
    }else {
        // The directory was not found.
        if (chdir(args[1]) < 0) {
            printf("%s: %i: cd: no such file or directory: %s\n", absolute_shell_name, cmd_count, args[1]);
        }
        // Change working directory to the specified directory in the argument of the 'cd' command.
        else {
            char new_dir[1024];
            getcwd(new_dir, sizeof(new_dir));
            setenv("OLDPWD", cur_dir, 1);
            setenv("PWD", new_dir, 1);
        }

    }

}

/**
 * print_working_dir - prints the working directory.
 */
void print_working_dir() {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else
        perror("pwd error");
}

/**
 * abs_name - finds the absolute name of the shell.
 * (Name of the shell including the path).
 *
 * @return: the absolute shell name.
 */
char *abs_name() {
    unsigned int i = 0;

    char tmp[1024];
    char tmp2[1024];

    _strcpy(tmp2, current_directory);

    if (shell_name[0] == '.' && shell_name[1] == '/') {
        while (shell_name[i + 1] != '\0') {
            *(tmp + i) = shell_name[i + 1];
            i++;
        }
        tmp[i] = '\0';
    } else {
        return shell_name;
    }

    _strcat(tmp2, tmp);

    return _strdup(tmp2);
}
