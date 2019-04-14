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
            for (int i = 0; i < sizeof(command) / sizeof(command[0]); i++)
            {
                arg[i] = command[2 + i];
            }
            unlink(arg);
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

int main()
{
    char *buffer;
    size_t bufsize = 32;
    size_t characters;
    buffer = (char *)malloc(bufsize * sizeof(char));

    while (true)
    {
        printf("SergioC&: ");
        characters = getline(&buffer, &bufsize, stdin);
        if (buffer[0] == 'p' && buffer[1] == 'w' && buffer[2] == 'd')
        {
            char *dir;
            size_t dirsize = 32;
            dir = (char *)malloc(dirsize * sizeof(char));
            dir = getcwd(dir, dirsize);
            printf("%s \n", dir);
        }
        if (buffer[0] == 'm' && buffer[1] == 'k' && buffer[2] == 'd' && buffer[3] == 'i' && buffer[4] == 'r')
        {
            char *arg;
            size_t argsize = characters - 7;
            arg = (char *)malloc(argsize * sizeof(char));
            for (int i = 0; i < argsize; i++)
            {
                arg[i] = buffer[6 + i];
            }
            mkdir(arg, S_IRWXU);
        }
        if (buffer[0] == 'c' && buffer[1] == 'd')
        {
            char *arg;
            size_t argsize = characters - 4;
            arg = (char *)malloc(argsize * sizeof(char));
            for (int i = 0; i < argsize; i++)
            {
                arg[i] = buffer[3 + i];
            }
            chdir(arg);
        }

        if (buffer[0] == 'r' && buffer[1] == 'm')
        {
            char *arg;
            size_t argsize = characters - 4;
            arg = (char *)malloc(argsize * sizeof(char));
            for (int i = 0; i < argsize; i++)
            {
                arg[i] = buffer[3 + i];
            }
            unlink(arg);
        }
        if (buffer[0] == 'n' && buffer[1] == 'a' && buffer[2] == 'n' && buffer[3] == 'o')
        {
            char *arg;
            size_t argsize = characters - 6;
            arg = (char *)malloc(argsize * sizeof(char));
            for (int i = 0; i < argsize; i++)
            {
                arg[i] = buffer[5 + i];
            }
            char *arg1[3] = {"/bin/nano", arg, NULL};

            if (fork() == 0)
            {

                execvp("/bin/nano", arg1);
                //				exit(0);
            }
            else
            {

                wait(NULL);
            }
        }
        if (buffer[0] == 'c' && buffer[1] == 'a' && buffer[2] == 't')
        {

            char *arg;
            size_t argsize = characters - 5;
            arg = (char *)malloc(argsize * sizeof(char));
            for (int i = 0; i < argsize; i++)
            {

                arg[i] = buffer[4 + i];
            }
            char *arg1[3] = {"/bin/cat", arg, NULL};

            if (fork() == 0)
            {

                execvp("/bin/cat", arg1);
            }
            else
            {
                wait(NULL);
            }
        }

        if (buffer[0] == 'l' && buffer[1] == 's')
        {
            DIR *dir;
            struct dirent *ti;
            dir = opendir(".");
            int i = 1;
            while (ti = readdir(dir))
            {
                printf("%s \t \t", ti->d_name);
                if ((i % 3) == 0)
                {
                    printf("\n");
                }
                i++;
            }
            printf("\n");
        }
    }
}