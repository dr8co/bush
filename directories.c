#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Changes the shell working directory.
 */
void change_directory() {
    char *old_dir = getenv("OLDPWD");

    // Handle 'cd', 'cd ~' and 'cd ~/' commands to change working directory to home directory.
    if ((args[1] == NULL) || (_strcmp(args[1], "~") == 0) || (_strcmp(args[1], "~/") == 0)) {
        if (chdir(home) == 0) {
            setenv("OLDPWD", cwd, 1);
            setenv("PWD", home, 1);
            getcwd(cwd, sizeof(cwd));

            // Update the prompt.
            free(prompt);
            prompt = replace_str(cwd, home, "~");
        }
    }
        // Handle 'cd -' command to change the working directory to the previous directory.
    else if (_strcmp(args[1], "-") == 0) {
        if (old_dir != NULL) {

            // change working dir to previous directory if exists.
            if (chdir(old_dir) == 0) {
                setenv("PWD", old_dir, 1);
                setenv("OLDPWD", cwd, 1);
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", old_dir);

                // Update the prompt.
                free(prompt);
                prompt = replace_str(cwd, home, "~");
            }
        }
            // change shell working directory to home directory if the old directory does not exist.
        else {
            if (chdir(home) == 0) {
                setenv("PWD", home, 1);
                setenv("OLDPWD", cwd, 1);
                getcwd(cwd, sizeof(cwd));
                printf("%s\n", home);

                // Update the prompt.
                free(prompt);
                prompt = replace_str(cwd, home, "~");
            }

        }
    }
        // Handle 'cd .' command.
    else if (_strcmp(args[1], ".") == 0) {
        setenv("OLDPWD", cwd, 1);
        setenv("PWD", cwd, 1);
    } else {
        // The directory was not found.
        if (chdir(args[1]) < 0) {
            printf("burning bush: %i: cd: no such file or directory: %s\n", cmd_count, args[1]);
        }
            // Change working directory to the specified directory in the argument of the 'cd' command.
        else {
            char new_dir[1024];
            getcwd(new_dir, sizeof(new_dir));
            setenv("OLDPWD", cwd, 1);
            setenv("PWD", new_dir, 1);
            getcwd(cwd, sizeof(cwd));

            // Update the prompt.
            free(prompt);
            prompt = replace_str(cwd, home, "~");
        }

    }

}

/**
 * @brief prints the working directory.
 */
void print_working_dir() {
    if (*cwd) {
        printf("%s\n", cwd);
    } else
        perror("error in reading current directory");
}

