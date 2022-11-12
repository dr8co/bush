#include "main.h"
#include <stdio.h>
#include <string.h>

void prompt() {
    char shell[1000];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(shell, "simple_shell:");
        strcat(shell, cwd);
        strcat(shell, "$ ");

        printf("%s", shell);
    } else
        perror("getcwd() error");

}