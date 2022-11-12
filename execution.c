#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void execute_pipe() {

    int i, n = 1, input, first;

    input = 0;
    first = 1;

    cmd_exec[0] = strtok(input_buffer, "|");

    while ((cmd_exec[n] = strtok(NULL, "|")) != NULL)
        n++;
    cmd_exec[n] = NULL;
    pipe_count = n - 1;
    for (i = 0; i < n - 1; i++) {
        input = split(cmd_exec[i], input, first, 0);
        first = 0;
    }
    input = split(cmd_exec[i], input, first, 1);
    input = 0;
    return;

}


void echo_calling(char *echo_val) {
    int i = 0, index = 0;
    environ_flag = 0;
    char new_args[1024], env_val[1000], *str[10];
    str[0] = strtok(echo_val, " ");
    str[1] = strtok(NULL, "");
    strcpy(env_val, args[1]);
    if (str[1] == NULL) {
        printf("\n");
        return;
    }
    if (strchr(str[1], '$')) {
        environ_flag = 1;
    }

    memset(new_args, '\0', sizeof(new_args));
    i = 0;
    while (str[1][i] != '\0') {
        if (str[1][i] == '"') {
            index = 0;
            while (str[1][i] != '\0') {
                if (str[1][i] != '"') {
                    new_args[index] = str[1][i];
                    flag = 1;
                    index++;
                }
                i++;
            }
        } else if (str[1][i] == 39) {
            index = 0;
            while (str[1][i] != '\0') {
                if (str[1][i] != 39) {
                    new_args[index] = str[1][i];
                    flag = 1;
                    index++;
                }
                i++;
            }
        } else if (str[1][i] != '"') {
            new_args[index] = str[1][i];
            index++;
            i++;
        } else i++;
    }


    new_args[index] = '\0';
    if ((strcmp(args[1], new_args) == 0) && (environ_flag == 0))
        printf("%s\n", new_args);
    else {
        strcpy(args[1], new_args);
        if (environ_flag == 1) {
            environ_ment();
        } else if (environ_flag == 0) {
            printf("%s\n", new_args);
        }
    }
}

void history_execute_with_constants() {
    int num, i, start_index;
    if (bang_flag == 1) {
        for (i = 0; i < no_of_lines; i++)
            printf("%s\n", history_data[i]);
    } else if (args[1] == NULL) {
        for (i = 0; i < no_of_lines - 1; i++)
            printf("%s\n", history_data[i]);
        printf(" %d %s\n", no_of_lines, his_var);
    } else {
        if (args[1] != NULL)
            num = atoi(args[1]);
        if (num > no_of_lines) {
            for (i = 0; i < no_of_lines - 1; i++)
                printf("%s\n", history_data[i]);
            printf(" %d %s\n", no_of_lines, his_var);
        }
        start_index = no_of_lines - num;
        for (i = start_index; i < no_of_lines - 1; i++)
            printf("%s\n", history_data[i]);
        printf(" %d %s\n", no_of_lines, his_var);
    }

}


void bang_execute() {
    char bang_val[1000];
    char *tokenise_bang[100], *num_ch[10];
    int i, n = 1, num, index = 0;
    i = 1;
    if (input_buffer[i] == '!') {
        strcpy(bang_val, history_data[no_of_lines - 1]);
    } else if (input_buffer[i] == '-') {
        n = 1;
        num_ch[0] = strtok(input_buffer, "-");
        while ((num_ch[n] = strtok(NULL, "-")) != NULL)
            n++;
        num_ch[n] = NULL;
        num = atoi(num_ch[1]);

        index = no_of_lines - num;
        strcpy(bang_val, history_data[index]);

    } else {
        num_ch[0] = strtok(input_buffer, "!");
        num = atoi(num_ch[0]);
        strcpy(bang_val, history_data[num - 1]);
    }
    tokenise_bang[0] = strtok(bang_val, " ");
    while ((tokenise_bang[n] = strtok(NULL, "")) != NULL)
        n++;
    tokenise_bang[n] = NULL;
    strcpy(bang_val, tokenise_bang[1]);
    printf("%s\n", bang_val);
    strcpy(input_buffer, bang_val);


}