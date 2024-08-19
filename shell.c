#include "shell.h"

/**
 * main - Entry point for the simple shell
 * @argc: Number of command line arguments
 * @argv: Array of command line arguments
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *input = NULL;
	size_t len = 0;
	ssize_t nread;
	char *cmd_array[MAX_CMD_ARGS];
	(void)argc;  /* Unused parameter */

	while (1)
	{
		/* Display the prompt */
		write(STDOUT_FILENO, "$ ", 2);

		/* Read input from user */
		nread = getline(&input, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin)) /* Handle EOF */
			{
				write(STDOUT_FILENO, "\n", 1);
				free(input);
				exit(EXIT_SUCCESS);
			}
			perror("getline");
			free(input);
			exit(EXIT_FAILURE);
		}

		/* Remove newline character from input */
		if (nread > 0 && input[nread - 1] == '\n')
		input[nread - 1] = '\0';

		/* Parse the input */
		parse_input(input, cmd_array);

		/* Execute the command */
		if (cmd_array[0] != NULL)
		execute(cmd_array);

		/* Clear the command array */
		clear_cmd_array(cmd_array);
	}

	free(input);
	return (EXIT_SUCCESS);
}

/**
 * parse_input - Parses the input string into an array of commands
 * @input: Input string to parse
 * @cmd_array: Array to hold parsed commands
 */
void parse_input(char *input, char *cmd_array[])
{
	int i = 0;
	char *token;

	token = strtok(input, " ");
	while (token != NULL && i < MAX_CMD_ARGS - 1)
	{
		cmd_array[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	cmd_array[i] = NULL;
}

/**
 * execute - Executes the command
 * @cmd_array: Array of commands to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute(char *cmd_array[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		/* Child process */
		if (execvp(cmd_array[0], cmd_array) == -1)
		{
			perror(cmd_array[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		do
		{
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid");
				return (-1);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}

/**
 * clear_cmd_array - Clears the command array
 * @cmd_array: Array of commands to clear
 */
void clear_cmd_array(char *cmd_array[])
{
	int i = 0;

	while (cmd_array[i] != NULL)
	{
		cmd_array[i] = NULL;
		i++;
	}
}
