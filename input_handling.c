#include <signal.h>
#include <stdio.h>
#include "main.h"

void sigintHandler(__attribute__((unused)) int sig_num) {
    signal(SIGINT, sigintHandler);
    fflush(stdout);
}