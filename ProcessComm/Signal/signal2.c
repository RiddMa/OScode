/* signal2.c */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/types.h>
int wait_flag;
void stop(){};
int main()
{
    int pid1, pid2;
    signal(3, stop); // 或者 signal(14, stop);
    while ((pid1 = fork()) == -1)
        ;
    if (pid1 > 0)
    {
        while ((pid2 = fork()) == -1)
            ;
        if (pid2 > 0)
        {
            wait_flag = 1;
            sleep(5);
            kill(pid1, 16);
            kill(pid2, 17);
            wait(0);
            wait(0);
            printf("Parent process is killed! !\n");
            exit(0);
        }
        else
        {
            wait_flag = 1;
            signal(17, stop);
            printf("Child process 2 is killed by parent!!\n");
            exit(0);
        }
    }
    else
    {
        wait_flag = 1;
        signal(16, stop);
        printf("Child process 1 is killed by parent!!\n");
        exit(0);
    }
    return 0;
}