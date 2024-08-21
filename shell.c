#include "main.h"

/**
 * command_read - Reads a command from stdin
 * @s: The command to read
 * Return: 0 on success, 1 on failure
 */

int command_read(char *s)
{
	int i;
	char *token = NULL;
	char *cmd_array[100];

	if (strcmp(s, "exit") == 0)
		return (2);
	if (strcmp(s, "env") == 0)
		return (_printenv());
	token = strtok(s, " ");
	i = 0;
	while (token != NULL && i < 100)
	{
		cmd_array[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	cmd_array[i] = NULL;
	return (execute(cmd_array));
}

/**
 * execute - Executes a command
 * @cmd_arr: The command to execute
 * Return: 0 on success, 1 on failure
 */

int execute(char *cmd_arr[])
{
	pid_t pid;
	char *exe_path;
	int status;

	exe_path = command_path(cmd_arr[0]);
	if (exe_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", cmd_arr[0]);
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error at creating a child process\n");
		exit (1);
	}
	if (pid > 0)
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (WEXITSTATUS(status) != 0)
		{
			exit(2);
		}
	}
	else if (pid == 0)
	{
		if (execvp(exe_path, cmd_arr) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", cmd_arr[0]);
			exit(127);
		}
	}
	free(exe_path);
	return (0);
}

/**
 * main - Entry point
 * @argc: The number of arguments
 * @argv: The arguments
 * Return: 0 on success, 1 on failure
 */

int main(void)
{
	char *line = NULL;
	size_t buf_size = 0;
	ssize_t characters = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "$ ", 2);
		characters = getline(&line, &buf_size, stdin);
		if (characters == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}
		if (line[characters - 1] == '\n')
			line[characters - 1] = '\0';
		trim_whitespace(line);
		if (*line == '\0')
			continue;
		if (command_read(line) == 2)
			break;
	}
	free(line);
	return (0);
}
