#include "main.h"
#include <stdio.h>

/**
 * @brief prints the regular prompt string.
 */
void print_prompt1() {
    if (user && prompt && *hostname) {
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

/**
 * @brief prints the prompt string for multiline input.
 */
void print_prompt2() {
    printf("> ");
}
