#include "main.h"
#include <string.h>
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

    if (home_dir == NULL) {
        home_dir = "/home";
    }
    if ((args[1] == NULL) || (strcmp(args[1], "~") == 0) || (strcmp(args[1], "~/") == 0))
        chdir(home_dir);
    else if (strcmp(args[1], "-") == 0) {
        if (old_dir != NULL) {
            chdir(old_dir);
        }
        else{
            printf("%s: %i: cd: OLDPWD not set\n", absolute_shell_name, cmd_count);
        }
    }
    else if (chdir(args[1]) < 0)
        printf("%s: %i: cd: can\'t cd to %s\n", absolute_shell_name, cmd_count, args[1]);

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

    strcpy(tmp2, current_directory);

    if (shell_name[0] == '.' && shell_name[1] == '/') {
        while (shell_name[i + 1] != '\0') {
            *(tmp + i) = shell_name[i + 1];
            i++;
        }
        tmp[i] = '\0';
    } else {
        return shell_name;
    }

    strcat(tmp2, tmp);
    return tmp2;
}
