#include "main.h"

/* Function to search for the command in PATH */
char *find_command_path(const char *cmd)
{
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *dir = strtok(path_copy, ":");
    char *full_path;
    struct stat st;

    while (dir != NULL)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2); /* +2 for '/' and '\0' */
        sprintf(full_path, "%s/%s", dir, cmd);

        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
        {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/* Define command_read */
int command_read(char *s)
{
    char *cmd_array[100];
    char *token;
    int i = 0;
    char *cmd_path;

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
    {
        cmd_path = find_command_path(cmd_array[0]);
        if (cmd_path != NULL)
        {
            int status;
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork");
                return 1;
            }
            if (pid == 0)
            {
                execv(cmd_path, cmd_array);
                perror(cmd_array[0]);
                exit(EXIT_FAILURE);
            }
            else
            {
                do {
                    waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
                free(cmd_path);

                if (WEXITSTATUS(status) != 0)
                {
                    return 1;
                }
            }
        }
        else
        {
            fprintf(stderr, "%s: command not found\n", cmd_array[0]);
            return 1;
        }
    }
    return 0;
}

/* Define _printenv function */
int _printenv(void)
{
    char **env = environ;
    while (*env != NULL)
    {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
