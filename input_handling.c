#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void sigintHandler(int sig_num) {
    if (sig_num == SIGINT) {
        printf("\n");
        print_prompt1();
    }
}

char *read_cmd(void) {
    char buff[1024];
    char *ptr = NULL;
    char ptr_len = 0;

    while (fgets(buff, 1024, stdin) != NULL) {
        int buff_len = _strlen(buff);

        if (!ptr) {
            ptr = malloc(buff_len + 1);
        } else {
            char *ptr2 = _realloc(ptr, ptr_len + buff_len + 1);

            if (ptr2) {
                ptr = ptr2;

            } else {
                free(ptr);
                ptr = NULL;
            }
        }

        if (!ptr) {
            perror("error: failed to alloc buffer");
            return NULL;
        }

        _strcpy(ptr + ptr_len, buff);

        if (buff[buff_len - 1] == '\n') {

            if (buff_len == 1 || buff[buff_len - 2] != '\\') {
                return ptr;
            }

            ptr[ptr_len + buff_len - 2] = '\0';
            buff_len -= 2;
            print_prompt2();
        }

        ptr_len += buff_len;
    }
    if (ptr == NULL) {
        printf("\n");
        exit(0);
    }

    return ptr;
}
