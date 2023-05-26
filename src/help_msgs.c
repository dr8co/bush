/**
 * @file help_msgs.c
 * @author Ian Duncan (dr8co@duck.com)
 * @brief file for help messages.
 * @version 3.0
 * @date 2023-05-27
 *
 * @copyright Copyright (c) 2023
 *
 */

/* 'help cd' */
char *cd_msg = "cd: cd [dir]\n"
               "\tChange the shell working directory.\n\n"

               "\tChange the current directory to DIR.  The default DIR is the value of the\n"
               "\tHOME shell variable.\n\n"

               "\tThe variable CDPATH defines the search path for the directory containing\n"
               "\tDIR.  Alternative directory names in CDPATH are separated by a colon (:).\n"
               "\tA null directory name is the same as the current directory.  If DIR begins\n"
               "\twith a slash (/), then CDPATH is not used.\n\n"

               "\tIf the directory is not found, an error message is printed.\n\n"

               "\tExit Status:\n"
               "\tReturns 0 if the directory is changed, -1 otherwise.\n";


/* 'help echo' */
char *echo_msg = "echo: echo [arg ...]\n"
                 "\tWrite arguments to the standard output.\n\n"

                 "\tDisplay the ARGs, separated by a single space character and followed by a\n"
                 "\tnewline, on the standard output.\n\n"

                 "\t \'echo\' interprets the following backslash-escaped characters:\n"
                 "\t\t\\a        alert (bell)\n"
                 "\t\t\\b        backspace\n"
                 "\t\t\\c        suppress further output\n"
                 "\t\t\\e        escape character\n"
                 "\t\t\\E        escape character\n"
                 "\t\t\\f        form feed\n"
                 "\t\t\\n        new line\n"
                 "\t\t\\r        carriage return\n"
                 "\t\t\\t        horizontal tab\n"
                 "\t\t\\v        vertical tab\n"
                 "\t\t\\\\        backslash\n"
                 "\t\t\\0nnn     the character whose ASCII code is NNN (octal).  NNN can be\n"
                 "\t\t\t  0 to 3 octal digits\n"
                 "\t\t\\xHH      the eight-bit character whose value is HH (hexadecimal).  HH\n"
                 "\t\t\t  can be one or two hex digits\n"
                 "\t\t\\uHHHH    the Unicode character whose value is the hexadecimal value HHHH.\n"
                 "\t\t\t  HHHH can be one to four hex digits.\n"
                 "\t\t\\UHHHHHHHH the Unicode character whose value is the hexadecimal value\n"
                 "\t\t\t  HHHHHHHH. HHHHHHHH can be one to eight hex digits.\n\n"

                 "\tExit Status:\n"
                 "\tReturns success unless a write error occurs.\n";

/* 'help exit' */
char *exit_msg = "exit: exit [n]\n"
                 "\tExit the shell.\n\n"

                 "\tExits the shell with a status of N.  If N is omitted, the exit status\n"
                 "\tis 0.\n";


/* 'help' */
char *help_msg = "The Burning Bush, version 3.0\n"
                 "These shell commands are defined internally.  Type 'help' to see this list.\n"
                 "Use 'man -k' or 'info' to find out more about commands not in this list.\n\n"

                 "\tcd [dir]\n"
                 "\techo [arg ...]\n"
                 "\texit [n]\n"
                 "\texport [name[=value] ...]\n"
                 "\tpwd\n"
                 "\thistory\n\n"

                 "Use 'man burning-bush' to learn more.\n";


/* 'help history' */
char *history_msg = "history: history [-c]\n"
                    "\tDisplay or manipulate the history list.\n\n"
                    "\tOptions:\n"
                    "\t\t-c	clear the history list by deleting all of the entries\n\n"
                    "\tExit Status:\n"
                    "\tReturns success unless an invalid option is given or an error occurs.\n";


/* 'help export' */
char *export_msg = "export: export [-fn] [name[=value] ...] or export -p\n"
                   "\tSet export attribute for shell variables.\n\n"

                   "\tMarks each NAME for automatic export to the environment of subsequently\n"
                   "\texecuted commands.  If VALUE is supplied, assign VALUE before exporting.\n\n"

                   "\tExit Status:\n"
                   "\tReturns success unless an invalid option is given or NAME is invalid.\n";


/* 'help help' */
char *help_help = "help: help [pattern ...]\n"
                  "\tDisplay information about builtin commands.\n\n"

                  "\tDisplays brief summaries of builtin commands.  If PATTERN is\n"
                  "\tspecified, gives detailed help on all commands matching PATTERN,\n"
                  "\totherwise the list of help topics is printed.\n\n"

                  "\tArguments:\n"
                  "\t  PATTERN 	Pattern specifying a help topic\n\n"

                  "\tExit Status:\n"
                  "\t  Returns success unless PATTERN is not found or an invalid option is given.\n";

/* version string */
char *version = "The Burning Bush 3.0, February 2023.\n"
                "Maintained by Ian Duncan at github.com/dr8co/bush\n"
                "License: MIT License. Use command 'license' to view the license.\n\n"
                "This is free software; you are free to change and redistribute it.\n"
                "There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";

char *LICENSE = "MIT License\n"
                "\n"
                "Copyright (c) 2023 Ian Duncan\n"
                "\n"
                "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                "of this software and associated documentation files (the \"Software\"), to deal\n"
                "in the Software without restriction, including without limitation the rights\n"
                "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
                "copies of the Software, and to permit persons to whom the Software is\n"
                "furnished to do so, subject to the following conditions:\n"
                "\n"
                "The above copyright notice and this permission notice shall be included in all\n"
                "copies or substantial portions of the Software.\n"
                "\n"
                "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
                "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
                "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
                "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
                "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
                "SOFTWARE.\n";
