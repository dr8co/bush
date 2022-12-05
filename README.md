# <div style="text-align: center;"> The Burning Bush: </div>
# <div style="text-align: center;"> A simple UNIX command interpreter </div>

![The Burning Bush](./media/burning_bush.png "The Burning Bush")

## Introduction

The Burning bush is a simple shell for
[UNIX-like operating systems](https://en.wikipedia.org/wiki/List_of_Unix_systems#Unix-like_operating_systems)
like Linux and macOS.
It is a bash (Bourne-Again Shell)-like, and is implemented in C.

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

* `cd [directory]`
changes the shell working directory. With no argument, the working directory
is changed to $HOME.
* `echo [args]`
Writes arguments to the standard output.
* `exit [status]`
Exits the shell with status (0 by default).
* `pwd`
Prints the shell working directory.
* `export [name[=value]]`
Export attribute for shell variables.
* `history`
display history of commands. '!' operator is also supported for executing
commands in the shell history. (eg `!!`, `!23`, `!3`).
* `help [command]`
Displays help. `help command` displays help for `command`, where `command`
can be `cd`, `echo`, and `exit`. `help`.
Without any argument, (or with an invalid argument),
the general shell help is printed.
* `env`
Prints environment variables.

### Other Features

* Piped commands (eg `ls | sort -r`).
* Handle interrupt signal: Ctrl-C does not terminate the shell.
* I/O redirection (<, >).
* `EOF` (Ctrl-D) exits the shell.
