#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define PROMPT "#cisfun$ "

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
        // Child process
        execlp(cmd, cmd, (char *)NULL);
        // If execlp returns, it must have failed
        perror(cmd);
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
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
        // Display the prompt
        printf(PROMPT);
        fflush(stdout);

        // Read the command from standard input
        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            // Handle end of file (Ctrl+D)
            if (feof(stdin))
            {
                printf("\n");
                free(line);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline");
                free(line);
                exit(EXIT_FAILURE);
            }
        }

        // Remove newline character from the end of the line
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        // If the command is empty, just display the prompt again
        if (strlen(line) == 0)
            continue;

        // Execute the command
        if (execute(line) != 0)
        {
            fprintf(stderr, "./shell: No such file or directory\n");
        }
    }

    // Clean up
    free(line);
    return 0;
}
