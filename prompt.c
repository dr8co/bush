#include "main.h"
#include <stdio.h>
#include <stdlib.h>

void print_prompt1() {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char *home = getenv("HOME");
        char *h = replace_str(cwd, home, "~");
        printf("%s@%s:%s$ ", user, hostname, h);
    } else {
        printf("$ ");
    }
}


void print_prompt2() {
    printf("> ");
}
