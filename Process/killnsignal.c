/* killnsignal.c */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void fun();
int main()
{
    int pid_c = -1;
    signal(17, fun);
    if (pid_c = fork())
    {
        printf("Parent speaking: Sending signal to child process.\n");
        kill(pid_c, 17);
        wait(0);
        printf("Parent speaking: finished.\n");
    }
    else
    {
        printf("%u\n",sleep(5));
        printf("Child speaking: I am here.\n");
        exit(0);
    }
    return 0;
}

void fun()
{
    printf("Signal received and processing.\n");
}