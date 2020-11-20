/* join.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread(void *argc)
{
    int i;
    for(i = 0;i<4;i++)
    {
        //sleep(1);
        printf("I'm a thread: counting %d.\n",i);
    }
}

int main()
{
    pthread_t tid;
    int i;
    pthread_create(&tid,NULL,thread,NULL);
    printf("Main thread: mic check 123123.\n");
    pthread_join(tid,NULL);
    for(i = 0;i<4;i++)
    {
        //sleep(1);
        printf("I'm the main thread: counting %d.\n",i);
    }
    return 0;
}