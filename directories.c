#include "main.h"
#include <string.h>
#include <stdio.h>

void change_directory() {
    char *h = "/home";
    if ((args[1]== NULL) || (strcmp(args[1], "~") == 0) || (strcmp(args[1], "~/") == 0))
        chdir(h);
    else if (chdir(args[1]) < 0)
        printf("bash: cd: %s: No such file or directory\n", args[1]);

}

void parent_directory() {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else
        perror("getcwd() error");


}