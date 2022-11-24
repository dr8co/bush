#include "main.h"
#include <stdio.h>

void print_prompt1() {
    char prompt[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        _strcpy(prompt, "My_shell:");
        _strcat(prompt, cwd);
        _strcat(prompt, "$ ");

        printf("%s", prompt);
    } else {
        printf("$ ");
    }
}


void print_prompt2() {
    printf("> ");
}
