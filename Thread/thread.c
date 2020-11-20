/* thread.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define THREAD_NUMBER 3
#define REPEAT_NUMBER 5
#define DELAY_TIME_LEVELS 10.0

void *t_fun(void *arg)
{
    int tid = (int)arg;
    int delay_time = 0;
    int count = 0;

    printf("Thread %d starting.\n", tid);
    for(count=0;count<REPEAT_NUMBER;count++)
    {
        delay_time = (int)(rand()*DELAY_TIME_LEVELS/(RAND_MAX))+1;
        sleep(delay_time);
        printf("\t Thread %d: job %d delay = %d.\n",tid,count,delay_time);
        
    }
    printf("Thread %d finished.\n", tid);
    pthread_exit(NULL);
}

int main(void)
{
    
}