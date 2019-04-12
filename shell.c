#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define size 200

int hasPrefix(char const *, char const *);
int cd(char *pth);
int main()
{

    char command[size];
    char *tok;
    tok = strtok(command, " ");

    while (command != NULL)
    {
        bzero(command, size);
        printf("OSAntonio$ ");
        fgets(command, size, stdin);
        if (hasPrefix(command, "cd") == 0)
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
        else if (hasPrefix(command, "ls") == 0)
        {
            system("ls");
        }
        else if (hasPrefix(command, "pwd") == 0)
        {
                }
    }
    return 0;
}

int hasPrefix(char const *p, char const *q)
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