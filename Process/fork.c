#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int pid_p, pid_c, rfork;
    if (rfork = fork())
    {
        pid_p = getpid();
        printf("pid of parent: %d\n", pid_p);
        printf("return of fork(): %d\n", rfork);
        printf("I am the parent process.\n");
    }
    else if (rfork == 0)
    {
        pid_c = getpid();
        printf("pid of child: %d\n", pid_c);
        printf("I am the child process.\n");
        exit(0);
    }
    else
    {
        printf("fork error.\n");
        exit(-1);
    }
    return 0;
}