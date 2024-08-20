#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
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

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (strlen(line) == 0)
            continue;

        if (command_read(line) == 2)
            break;
    }

    free(line);
    return 0;
}
