#include <stdio.h>
#include <unistd.h>

extern char **environ;
int main(int argc, char *argv[])
{
    int index = 0;
    printf("Environment variables:\n");
    index = 0;
    while (environ[index])
    {
        printf("envp[%d]: %s\n", index, environ[index]);
        ++index;
    }
    return 0;
}

