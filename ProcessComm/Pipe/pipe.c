/* pipe.c */
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int pid; //process id
int main()
{
    int fd[2];
    //char array for pipe
    char outpip[100], inpip[100];
    //create pipe
    pipe(fd);

    while ((pid = fork()) == -1)
        ; //infinite loop if pipe did not create
    if (pid == 0)
    {
        lockf(fd[1], 1, 0);                                     //lock pipe
        sprintf(outpip, "Child process is sending message.\n"); //put msg into array
        write(fd[1], outpip, 50);                               //write 50 byte to pipe
        sleep(5);
        lockf(fd[1], 0, 0);
        exit(0);
    }
    else
    {
        wait(0);                //wait for child process
        read(fd[0], inpip, 50); //read 50 byte from pipe
        printf("%s", inpip);    //display bytes
        exit(0);                //end parent process
    }
    return 0;
}