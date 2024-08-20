#include "shell.h"


/**
* _printenv - prints the environment
*
* Return: 0 on success, -1 on failure
*/
int _printenv(void)
{
	int i;

	if (environ == NULL)
		return (-1);

	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);

	return (0);
}

/**
* execute - executes the command
* @cmd_arr: the command line
*
* Return: 0 on success, -1 on failure
*/
int execute(char *cmd_arr[])
{
	int status;
	pid_t child_pid;

	child_pid = fork();


	if (child_pid == 0)
	{
		if (execvp(cmd_arr[0], cmd_arr) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else if (child_pid >= -1)
		wait(&status);
	else
	{
		perror("fork");
		return (-1);
	}

	return (0);
}

/**
* command_tok - tokenizes the command line
* @line: the command line
*
* Return: execute function
*/
int command_tok(char *line)
{
	int count = 0;
	char *exec_args[128], *token;

	token = strtok(line, " ");

	while (token != NULL)
	{
		exec_args[count] = token;
		count++;
		token = strtok(NULL, " ");
	}

	exec_args[count] = NULL;

	return (execute(exec_args));
}
