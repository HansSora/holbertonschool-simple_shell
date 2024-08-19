# Simple Shell 

Simple Shell is project written using the C-programming language with the object of creating a basic version of a Unix shell able to intepret and execute commands provided by the use.



## Description

This **Simple Shell** can:

- Display a prompt and wait for the user to type a command.
```shell
./hsh
$ ls
command_path.c shell.c string_utils.c README.md
$
```
- The prompt is displayed again each time a command has been executed.
- If an executable cannot be found, prints an error message and displays the prompt again.
```shell
./hsh
$ hello
hello: Not found
$ 
```
- Handles errors.
- Handles the "end of file" condition (`Ctrl+D`)

Also works in interactive and non-interactive mode:
- interactive mode
```shell
./hsh
$ /bin/ls
AUTHORS README.md command_path.c shell.c shell.h
$
```
- non-interactive mode
```shell
$ echo "/bin/ls" | ./hsh
AUTHORS README.md command_path.c shell.c shell.h
$
```

**Compiling**

The code can be compiled using **gcc** with additional attributes as follows. It produces an executable file named **hsh**.

## Code Structure

To develop the simple shell, we have built fundamental functionalities that allow to read a command provided by the user, process it, and execute it by referencing the respective Unix system call.

1. manipulating string files 
2. accessing and displaying environment variables
3. accessing the full path of any Unix shell command
4. reading and executing any shell command.


## Authors

- [Gerti Bajo] <https://github.com/Gerti23>
- [Hans Sora] <https://github.com/HansSora>
