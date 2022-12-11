cmake_minimum_required(VERSION 3.23)

add_executable(bush
        directories.c environment.c execution.c
        history.c main.h
        main.c memory.c numbers.c process_cmd.c
        prompt.c strings_1.c strings_2.c
        help.c help_msgs.c get_info.c signal_handler.c fileops.c)
