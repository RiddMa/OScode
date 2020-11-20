/*fork.c*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    int pid;
    if ((pid = fork()) > 0)
    {
        printf("pid:%d\n", pid);
        printf("I am the parent process.\n");
        /*父进程处理过程*/
    }
    else if (pid == 0)
    {
        printf("I am the child process.\n");
        /*子进程处理过程*/
        exit(0);
    }
    else
    {
        printf("fork error\n");
        exit(0);
    }
    return 0;
}