/* wait.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char **argv)
{
    int pid_p = -1, pid_c = -1, rfork = -1, rwait = -1;
    if (rfork = fork())
    {
        pid_p = getpid();
        printf("Parent process: %d\n", pid_p);
        rwait = wait(NULL);
        printf("return of fork() = %d, return of wait() = %d\n", rfork, rwait);
    }
    else
    {
        pid_c = getpid();
        printf("Child process\n");
        printf("return of fork() = %d, pid of child = %d\n", rfork, pid_c);
        exit(0);
    }
    return 0;
}