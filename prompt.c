#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void print_prompt1() {
    if (*cwd) {

        printf("\033[1;34m");
        printf("%s@%s", user, hostname);
        printf("\033[0m");
        printf(":");
        printf("\033[1;35m");
        printf("%s", prompt);
        printf("\033[0m");
        printf("$ ");

    } else {
        printf("$ ");
    }
}


void print_prompt2() {
    printf("> ");
}
