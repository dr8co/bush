#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void print_prompt1() {
    if (*cwd) {
        printf("%s@%s:%s$ ", user, hostname, prompt);
    } else {
        printf("$ ");
    }
}


void print_prompt2() {
    printf("> ");
}
