#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Define the maximum number of command arguments */
#define MAX_CMD_ARGS 128

/**
 * parse_input - Parses the input string into an array of commands
 * @input: Input string to parse
 * @cmd_array: Array to hold parsed commands
 */
void parse_input(char *input, char *cmd_array[]);

/**
 * execute - Executes the command
 * @cmd_array: Array of commands to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute(char *cmd_array[]);

/**
 * clear_cmd_array - Clears the command array
 * @cmd_array: Array of commands to clear
 */
void clear_cmd_array(char *cmd_array[]);

#endif /* SHELL_H */
