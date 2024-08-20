#include "shell.h"

/* Define the _printenv function */
int _printenv(void)
{
    /* Implementation for printing environment variables */
    /* Ensure this function is implemented properly */
    return 0;
}

/* Define command_read */
int command_read(char *s)
{
    char *cmd_array[100];
    char *token;
    int i = 0;

    if (strcmp(s, "exit") == 0)
        return 2;
    if (strcmp(s, "env") == 0)
        return _printenv();

    token = strtok(s, " ");
    while (token != NULL && i < 100)
    {
        cmd_array[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    cmd_array[i] = NULL;

    if (cmd_array[0] != NULL)
        return execute(cmd_array); /* Call to execute */

    return 1;
}

/* Define execute */
int execute(char *cmd_arr[])
{
    pid_t pid;
    int status;
    char *cmd = cmd_arr[0];

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 1;
    }
    if (pid == 0)
    {
        execvp(cmd, cmd_arr);
        perror(cmd);
        exit(EXIT_FAILURE);
    }
    else
    {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));

        if (WEXITSTATUS(status) != 0)
        {
            return 1;
        }
    }
    return 0;
}
