/* signal1.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int flag_wait = 1;

void stop_child()
{
    flag_wait = 0;
    printf("\nChild interruption.\n");
}

void stop()
{
    printf("\nInterruption.\n");
}

int main()
{
    pid_t pid1, pid2;
    signal(3, stop);
    while ((pid1 = fork()) == -1)
        ;
    if (pid1)
    {
        while ((pid2 = fork()) == -1)
            ;
        if (pid2) //child process 2
        {
            sleep(1);
            kill(pid1, 16);
            wait(0);
            kill(pid2, 17);
            wait(0);
            printf("\nParent process is killed.\n");
            exit(0);
        }
        else //child process 1
        {
            signal(17, stop_child);
            while (flag_wait)
                ;
            printf("\nChild process 2 is killed.\n");
            exit(0);
        }
    }
    else //parent process
    {
        signal(16, stop_child);
        while (flag_wait)
            ;
        printf("\nChild process 1 is killed.\n");
        exit(0);
    }
    return 0;
}