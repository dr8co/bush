#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>
#include "main.h"

char *skip_comma(char *str) {
    int i = 0, j = 0;
    char temp[1000];
    while (str[i++] != '\0') {
        if (str[i - 1] != '"')
            temp[j++] = str[i - 1];
    }
    temp[j] = '\0';
    str = strdup(temp);

    return str;
}

char *skip_whitespaces(char *s) {
    while (isspace(*s)) ++s;
    return s;
}

int split(char *cmdExec, int input, int first, int last) {
    char *new_cmd_exec1;
    new_cmd_exec1 = strdup(cmdExec);
    {
        int m = 1;
        args[0] = strtok(cmdExec, " ");
        while ((args[m] = strtok(NULL, " ")) != NULL)
            m++;
        args[m] = NULL;
        if (args[0] != NULL) {

            if (strcmp(args[0], "exit") == 0)
                exit(0);
            if (strcmp(args[0], "echo") != 0) {
                cmdExec = skip_comma(new_cmd_exec1);
                int n = 1;
                args[0] = strtok(cmdExec, " ");
                while ((args[n] = strtok(NULL, " ")) != NULL)
                    n++;
                args[n] = NULL;

            }
            if (strcmp("cd", args[0]) == 0) {
                change_directory();
                return 1;
            } else if (strcmp("pwd", args[0]) == 0) {
                parent_directory();
                return 1;
            }

        }
    }
    return command(input, first, last, new_cmd_exec1);
}
