#include "shell.h"

/**
 * command_read - Reads a command from stdin and executes it.
 * @s: The command to read.
 * Return: 0 on success, 1 on failure, 2 to indicate exit.
 */
int command_read(char *s)
{
    char *cmd_array[100];
    char *token;
    int i = 0;

    if (strcmp(s, "exit") == 0)
        return (2);
    if (strcmp(s, "env") == 0)
        return (_printenv());

    token = strtok(s, " ");
    while (token != NULL && i < 100)
    {
        cmd_array[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    cmd_array[i] = NULL;

    // Execute the first command in cmd_array
    if (cmd_array[0] != NULL)
        return (execute(cmd_array[0]));

    return (1);
}

/**
 * execute - Executes a command.
 * @cmd: The command to execute.
 * Return: 0 on success, 1 on failure.
 */
int execute(char *cmd)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        /* Child process */
        execlp(cmd, cmd, (char *)NULL);
        /* If execlp returns, it must have failed */
        perror(cmd);
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        if (WEXITSTATUS(status) != 0)
        {
            return 1;  /* Return 1 to indicate failure */
        }
    }
    return 0;
}

/**
 * main - Entry point of the shell.
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        /* Display the prompt */
        printf("#cisfun$ ");
        fflush(stdout);

        /* Read the command from standard input */
        nrea
