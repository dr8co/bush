cmake_minimum_required(VERSION 3.23)
project(simple_shell C)

set(CMAKE_C_STANDARD 90)

add_executable(simple_shell
        directories.c environment.c execution.c
        file_handling.c input_handling.c main.h
        main.c memory.c numbers.c process_cmd.c
        prompt.c strings_1.c tokenize.c)
