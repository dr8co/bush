cmake_minimum_required(VERSION 3.23)
project(bush C)

set(CMAKE_C_STANDARD 17)

add_executable(bush
        directories.c environment.c execution.c
        history.c input_handling.c main.h
        main.c memory.c numbers.c process_cmd.c
        prompt.c strings_1.c tokenize.c strings_2.c help.c)
