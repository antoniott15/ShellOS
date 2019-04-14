#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#define size 200

int hasArguments(char const *, char const *);
int cd(char *pth);
int main()
{

    char command[size], argument2;
    char *tok;
    tok = strtok(command, " ");

    while (command != NULL)
    {
        bzero(command, size);
        printf("OSAntonio$ ");
        fgets(command, size, stdin);
        if (hasArguments(command, "cd") == 0)
        {
            tok = strchr(command, ' ');
            if (tok)
            {
                char *tempTok = tok + 1;
                tok = tempTok;
                char *locationOfNewLine = strchr(tok, '\n');
                if (locationOfNewLine)
                {
                    *locationOfNewLine = '\0';
                }
                cd(tok);
            }
        }
        else if (hasArguments(command, "pwd") == 0)
        {
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));
            printf(cwd);
        }

        else if (hasArguments(command, "ls") == 0)
        {
            {
                DIR *dir;
                struct dirent *ti;
                dir = opendir(".");
                int i = 1;
                while (ti = readdir(dir))
                {
                    printf("%s ", ti->d_name);
                    if ((i % 2) == 0)
                    {
                        printf("\n");
                    }
                    i++;
                }
                printf("\n");
            }
        }

        else if (command[0] == 'r' && command[1] == 'm')
        {
            char *arg;
            size_t argument = sizeof(command) - 3;
            arg = (char *)malloc(argument * sizeof(char));
            for (int i = 0; i < argument; i++)
            {
                arg[i] = command[2 + i];
            }
            unlink(arg);
        }

        if (command[0] == 'n' && command[1] == 'a' && command[2] == 'n' && command[3] == 'o')
        {
            char *arg;
            size_t argument = sizeof(command) - 5;
            arg = (char *)malloc(argument * sizeof(char));
            for (int i = 0; i < argument; i++)
            {
                arg[i] = command[4 + i];
            }
            char *arg1[3] = {"/bin/nano", arg, NULL};

            if (fork() == 0)
            {
                execvp("/bin/nano", arg1);
            }
            else
            {
                wait(NULL);
            }
        }
        else if (hasArguments(command, "exit") == 0)
        {
            break;
        }
    }
    return 0;
}

int hasArguments(char const *p, char const *q)
{
    int i = 0;
    for (i = 0; q[i]; i++)
    {
        if (p[i] != q[i])
            return -1;
    }
    return 0;
}

int cd(char *pth)
{
    char path[size];
    strcpy(path, pth);

    char cwd[size];
    if (pth[0] != '/')
    {
        getcwd(cwd, sizeof(cwd));
        strcat(cwd, "/");
        strcat(cwd, path);
        chdir(cwd);
    }
    else
    {
        chdir(pth);
    }

    return 0;
}
