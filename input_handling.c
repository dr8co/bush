#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "main.h"

void sigintHandler(__attribute__((unused)) int sig_num) {
    signal(SIGINT, sigintHandler);
    fflush(stdout);
}

char *read_cmd(void)
{
    char buff[1024];
    char *ptr = NULL;
    char ptr_len = 0;

    while(fgets(buff, 1024, stdin) != NULL)
    {
        int buff_len = _strlen(buff);

        if(!ptr)
        {
            ptr = malloc(buff_len + 1);
        }
        else
        {
            char *ptr2 = realloc(ptr, ptr_len + buff_len + 1);

            if(ptr2)
            {
                ptr = ptr2;

            }
            else
            {
                free(ptr);
                ptr = NULL;
            }
        }

        if(!ptr)
        {
            fprintf(stderr, "error: failed to alloc buffer: %s\n", strerror(errno));
            return NULL;
        }

        strcpy(ptr + ptr_len, buff);

        if(buff[buff_len - 1] == '\n')
        {

            if(buff_len == 1 || buff[buff_len - 2] != '\\')
            {
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
