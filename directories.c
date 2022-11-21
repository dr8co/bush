#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/* Global Variables */
char *shell_name;
char *absolute_shell_name;
char current_directory[1024];
char cwd[1024];

void change_directory() {
    char *home_dir = getenv("HOME");
    char *old_dir = getenv("OLDPWD");
    char cur_dir[1024];

    getcwd(cur_dir, sizeof(cur_dir));

    if (home_dir == NULL) {
        home_dir = "/home";
    }
    if ((args[1] == NULL) || (_strcmp(args[1], "~") == 0) || (_strcmp(args[1], "~/") == 0)) {
        if (chdir(home_dir) == 0) {
            setenv("OLDPWD", cur_dir, 1);
            setenv("PWD", home_dir, 1);
        }
    } else if (_strcmp(args[1], "-") == 0) {
        if (old_dir != NULL) {
            if (chdir(old_dir) == 0) {
                setenv("PWD", old_dir, 1);
                setenv("OLDPWD", cur_dir, 1);
                printf("%s\n", old_dir);
            }
        } else {
            if (chdir(home_dir) == 0) {
                setenv("PWD", home_dir, 1);
                setenv("OLDPWD", cur_dir, 1);
                printf("%s\n", home_dir);
            }

            //printf("%s: %i: cd: OLDPWD not set\n", absolute_shell_name, cmd_count);
        }
    } else if (_strcmp(args[1], ".") == 0) {
        setenv("OLDPWD", cur_dir, 1);
        setenv("PWD", cur_dir, 1);
    } else {
        if (chdir(args[1]) < 0) {
            printf("%s: %i: cd: can\'t cd to %s\n", absolute_shell_name, cmd_count, args[1]);
        } else {
            char new_dir[1024];
            getcwd(new_dir, sizeof(new_dir));
            setenv("OLDPWD", cur_dir, 1);
            setenv("PWD", new_dir, 1);
        }

    }

}

void parent_directory() {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else
        perror("getcwd() error");
}

char *abs_name() {
    unsigned int i = 0;

    char *tmp = malloc(sizeof(char) * 1024);
    char *tmp2 = malloc(sizeof(char) * 1024);

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
    return tmp2;
}
