/* id.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread(void *arg)
{
    printf("New thread: I'm a new thread.\n");
    printf("New thread: my tid is %u.\n",(unsigned int)pthread_self());
    printf("New thread: my pid is %d.\n",getpid());
}

int main()
{
    pthread_t tid;
    printf("Main thread: starting...\n");
    if(pthread_create(&tid,NULL,thread,NULL)!=0)
    {
        printf("Thread creation failed.\n");
        return -1;
    }
    printf("Main process pid is %d.\n",getpid());
    sleep(1);
    return 0;
}