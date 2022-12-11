/**
 * @file signal_handler.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief source file for input handling
 * @version 1.0
 * @date 2022-12-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <signal.h>
#include <stdio.h>
#include "main.h"

/**
 * @brief handle signals.
 * @param sig_num - the signal number.
 */
void signalHandler(int sig_num) {
    if (sig_num == SIGINT) {
        printf("\n");
        print_prompt1();
        fflush(stdout);
    }
}
