# The Burning Bush: A simple UNIX command interpreter

![The Burning Bush](./media/burning_bush.png "The Burning Bush")

## Table of Content

* [About](#introduction)
* [Usage](#usage)
  * [Requirements](#requirements)
  * [Compilation](#compilation)
* [Features](#features)
  * [Supported Commands](#supported-commands)
  * [Other Features](#other-features)
* [Examples](#examples)

## Introduction

The Burning bush is a simple shell for
[UNIX-like operating systems](https://en.wikipedia.org/wiki/List_of_Unix_systems#Unix-like_operating_systems).
It is a bash (Bourne-Again Shell)-like, and is implemented in C.

This project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

## Usage

### Requirements

* UNIX-like evironment, like macOS and Linux.
* gcc C compiler, or clang C compiler.

### Compilation

Compile with `-Wall -Werror -Wextra -pedantic` flags to generate warnings for potential issues/bugs.

Use option `-std=gnuXX` where `XX` can be `99`, `11`, `17` or `2x`, depending on the
latest version of C supported by your compiler
(it is advisable to compile with the latest stable standards).

For example,

```zsh
gcc -Wall -Werror -Wextra -pedantic -std=gnu2x *.c -o bush
# or
clang -Wall -Werror -Wextra -pedantic -std=gnu2x *.c -o bush
```

Alternatively, you can build using CMake.

## Features

### Supported Commands

The Burning Bush supports all the standard UNIX commands (every program in PATH)
as well as a few builtin commands.

The builtins supported are:

* `cd [directory]`\
Changes the shell working directory. With no argument
(or with `~` or `~/` arg), the working directory
is changed to $HOME.
`cd -` changes the working directory to the previous working directory.

* `echo [args]`\
Writes arguments to the standard output.

* `exit [status]`\
Exits the shell with status (0 by default or if called with no argument).

* `pwd`\
Prints the shell working directory.

* `export [name[=value]]`\
Export attribute for shell variables.

* `history`\
Display history of commands. '!' operator is also supported for executing
commands in the shell history. (eg `!!`, `!23`, `!3`).

* `help [command]`\
Displays help. `help command` displays help for `command`, where `command`
can be `cd`, `echo`, and `exit`. `help`.
Without any argument, (or with an invalid argument),
the general shell help is printed.

* `env`\
Prints environment variables.

### Other Features

* Piped commands (eg `ls | sort -r`).
* Handle interrupt signal: Ctrl-C does not terminate the shell.
* I/O redirection (<, >).
* `EOF` (Ctrl-D) exits the shell.
* Bash-style multiline commands (commands ending with '\\').
* The primary and secondary prompts are similar to the defaults of bash:

```console
# primary:
username@hostname:current_working_directory$
# secondary:
>
```

## Examples

```console
normal@prompt:bush$ gcc -Wall -Werror -Wextra -pedantic -std=gnu2x *.c -o bush

normal@prompt:bush$ ./bush

ian@github:bush$ help
The Burning Bush, version 1.0.0
These shell commands are defined internally.  Type 'help' to see this list.
Use 'man -k' or 'info' to find out more about commands not in this list.

cd [dir]
echo [arg ...]
exit [n]
export [name[=value] ...]
pwd
history

ian@github:bush$ ls -l | sort -r
total 104
-rw-rw-r-- 1 ian ian  834 Dec  5 18:44 help.c
-rw-rw-r-- 1 ian ian  801 Dec  2 21:51 prompt.c
-rw-rw-r-- 1 ian ian 6381 Dec  5 18:44 execution.c
-rw-rw-r-- 1 ian ian  463 Dec  5 18:44 signal_handler.c
-rw-rw-r-- 1 ian ian 4608 Dec  5 18:44 strings_1.c
-rw-rw-r-- 1 ian ian 4032 Dec  5 18:44 strings_2.c
-rw-rw-r-- 1 ian ian 3844 Dec  5 21:33 history.c
-rw-rw-r-- 1 ian ian 3502 Dec  5 18:44 process_cmd.c
-rw-rw-r-- 1 ian ian 3452 Dec  5 21:32 main.c
-rw-rw-r-- 1 ian ian 3323 Dec  5 18:44 help_msgs.c
-rw-rw-r-- 1 ian ian  328 Dec  5 18:44 CMakeLists.txt
-rw-rw-r-- 1 ian ian 3277 Dec  5 22:08 README.md
-rw-rw-r-- 1 ian ian 3222 Dec  5 18:44 directories.c
-rw-rw-r-- 1 ian ian 2657 Dec  5 21:11 get_info.c
-rw-rw-r-- 1 ian ian 2419 Dec  5 18:44 fileops.c
-rw-rw-r-- 1 ian ian 2386 Dec  5 21:23 main.h
-rw-rw-r-- 1 ian ian 1827 Dec  5 18:44 environment.c
-rw-rw-r-- 1 ian ian 1454 Dec  5 18:44 memory.c
-rw-rw-r-- 1 ian ian 1426 Dec  5 18:44 numbers.c
-rw-rw-r-- 1 ian ian  108 Nov 21 15:43 AUTHORS
-rw-rw-r-- 1 ian ian 1067 Nov 21 15:43 LICENSE
drwxrwxr-x 2 ian ian 4096 Nov 28 17:13 media

ian@github:bush$ echo $HOME
home/ian

ian@github:bush$ whoami > me.txt

ian@github:bush$ cat me.txt
ian

ian@github:bush$ echo $U\
>SER
ian

ian@github:bush$ tail main.h
void print_prompt1();
void print_prompt2();

/* help.c */
void find_help(const char *str);

/* signal_handler.c */
void signalHandler(int sig_num);

#endif /* MAIN_H */

ian@github:bush$ exit 98

normal@prompt:bush$ echo $?
98
```
