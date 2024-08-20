#include "shell.h"

/**
 * main - Entry point of the program
 *
 * Return: 0 on normal exit, EXIT_FAILURE on error
 */
int main(void)
{
	int chars_read, istty;
	char *buff = NULL;
	size_t size = 0;

	while (1)
	{
		istty = isatty(STDIN_FILENO);
		if (istty == 1)
			printf("$ ");

		chars_read = getline(&buff, &size, stdin);

		if (chars_read == -1)
		{
			perror("Error reading input");
			if (buff)
				free(buff);
			exit(EXIT_FAILURE);
		}

		if (strcmp(buff, "env") == 0)
		{
			_printenv();
			continue;
		}

		if (strcmp(buff, "\0") == 0)
			continue;
		if (strcmp(buff, "exit\n") == 0)
			break;

		if (buff[chars_read - 1] == '\n')
			buff[chars_read - 1] = '\0';

		command_tok(buff);
		if (istty != 1)
			break;
	}
	free(buff);
	return (0);
}
