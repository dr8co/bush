<h1 align="center">The Burning Bush</h1>
<h2 align="center">A simple UNIX command interpreter</h2>

<p align="center">
<img alt="The Burning Bush" src="./media/mother-earth-burning.gif" title="Mother Earth Burning Sticker" width="491" height="495"/>
</p>

## Table of Contents

* [About](#introduction)
* [Installation](#installation)
    * [Requirements](#requirements)
    * [How to install](#how-to-install)
* [Usage](#usage)
    * [Supported Commands](#supported-commands)
    * [Other features](#other-features)
* [Examples](#examples)
* [Uninstallation](#uninstallation)
* [Caveats](#caveats)
* [Acknowledgement](#acknowledgement)

## Introduction

The Burning bush is a simple shell for
[UNIX-like operating systems](https://en.wikipedia.org/wiki/List_of_Unix_systems#Unix-like_operating_systems).
It is a bash (Bourne-Again Shell)-like, and is implemented in C.

Some string functions found in `<string.h>` header have been re-implemented in this project
(for learning purposes).

This project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

## Installation

### Requirements

* **UNIX-like environment**, like macOS and Linux.
* GNU **GCC**, or LLVM **Clang** compiler.

### How to install

Run the [installation script](./install.sh) with root privileges to install:

```zsh
sudo ./install.sh
```

Additionally, you can compile The Burning Bush instead of installing it in your system
using the compile.sh script.

Also, you can compile it on the command-line with
`-Wall -Werror -Wextra -pedantic` flags to generate warnings for potential issues/bugs.

Use option `-std=gnuXX` where `XX` can be `99`, `11`, `17` or `2x`, depending on the
latest version of C supported by your compiler.

For example,

```zsh
gcc -Wall -Werror -Wextra -pedantic -std=gnu2x *.c -o bush
# or
clang -Wall -Werror -Wextra -pedantic -std=gnu2x *.c -o bush
```

Alternatively, you can build using CMake and Ninja:

```zsh
mkdir -p ./cmake-bush

"$(command -v cmake)" -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="$(command -v ninja)" -G Ninja -S . -B ./cmake-bush

"$(command -v cmake)" --build ./cmake-bush --target bush -j 4

# You can now run
# cd cmake-bush/src && ./bush

```

## Usage

Run the compiled executable to invoke the shell on the terminal,
or invoke with `bush` command on the terminal to initiate a session
if the program was successfully installed in your system.

Terminate with `exit`.

### Supported Commands

The Burning Bush supports all the standard UNIX commands (every program in PATH)
as well as a few builtin commands.

The **builtins** supported are:

* `cd [directory]`\
  Changes the shell working directory. With no argument
  (or with `~` or `~/` arg), the working directory
  is changed to $HOME.
  `cd -` changes the working directory to the previous working directory.

* `exit [status]`\
  Exits the shell with status (0 by default or if called with no argument).

* `pwd`\
  Prints the shell working directory.

* `export [name[=value]]`\
  Export attribute for shell variables.

* `history`\
  Display history of commands.\
  The `!` operator is also supported for executing
  commands in the shell history. (eg `!!`, `!23`, `!3`).

* `help [command]`\
  Displays help. `help command` displays help for `command`, where `command`
  can be `cd`, `echo`, and `exit`. `help`.
  Without any argument, (or with an invalid argument),
  the general shell help is printed.

### Other Features

* Piped commands (eg `ls | sort -r`).
* Handle interrupt signal: Ctrl-C does not terminate the shell.
* I/O redirection (<, >).
* `EOF` (Ctrl-D) exits the shell.
* Bash-style multiline commands (commands ending with '\\').
* Glob expansion (**experimental**).
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

ian@github:bush$ ls -l src/ | grep "a" | sort -r
total 88
-rw-rw-r-- 1 ian ian  973 Dec 12 23:29 globs.c
-rw-rw-r-- 1 ian ian  801 Dec 11 16:02 prompt.c
-rw-rw-r-- 1 ian ian 6397 Dec 11 16:02 execution.c
-rw-rw-r-- 1 ian ian 4918 Dec 11 16:02 help_msgs.c
-rw-rw-r-- 1 ian ian  463 Dec 11 16:02 signal_handler.c
-rw-rw-r-- 1 ian ian 4608 Dec 11 16:02 strings_1.c
-rw-rw-r-- 1 ian ian 4032 Dec 11 16:02 strings_2.c
-rw-rw-r-- 1 ian ian 3976 Dec 11 16:02 history.c
-rw-rw-r-- 1 ian ian 3502 Dec 16 22:50 process_cmd.c
-rw-rw-r-- 1 ian ian 3460 Dec 11 16:02 main.c
-rw-rw-r-- 1 ian ian 3222 Dec 11 16:02 directories.c
-rw-rw-r-- 1 ian ian  294 Dec 12 16:48 CMakeLists.txt
-rw-rw-r-- 1 ian ian 2889 Dec 11 16:02 get_info.c
-rw-rw-r-- 1 ian ian 2603 Dec 11 16:02 fileops.c
-rw-rw-r-- 1 ian ian 2407 Dec 12 19:24 main.h
-rw-rw-r-- 1 ian ian 1807 Dec 11 16:02 environment.c
-rw-rw-r-- 1 ian ian 1454 Dec 11 16:02 memory.c
-rw-rw-r-- 1 ian ian 1378 Dec 17 23:49 numbers.c
-rw-rw-r-- 1 ian ian 1243 Dec 11 16:02 help.c

ian@github:bush$ echo $HOME
home/ian

ian@github:bush$ whoami > me.txt

ian@github:bush$ cat me.txt
ian

ian@github:bush$ echo "This is a \
> multi-line command."
This is a multi-line command.

ian@github:bush$ tail main.h
void print_prompt1();
void print_prompt2();

/* help.c */
void find_help(const char *str);

/* signal_handler.c */
void signalHandler(int sig_num);

#endif /* MAIN_H */

ian@github:bush$ ls *.sh
compile.sh  install.sh	uninstall.sh

ian@github:bush$ exit 98

normal@prompt:bush$ echo $?
98
```

## Uninstallation

Run the [uninstallation script](./uninstall.sh) with root privileges to uninstall
The Burning Bush from your system:

```zsh
sudo ./uninstall.sh
```

## Caveats

* Command separators `;`, `||`, `&&` are not supported.
* No support for background jobs.
* Wildcard expansion/ matching is not fully stable.

## Acknowledgement

Project author: [Ian Duncan](https://github.com/dr8co "Ian")

The **"Mother Earth Burning Sticker"** courtesy of [Tenor](https://tenor.com/ "Tenor")
and [INTO ACTION](https://tenor.com/official/intoaction "intoaction").
It can be found
[here](https://tenor.com/view/mother-earth-burning-fire-on-fire-wildfire-gif-18417870).
