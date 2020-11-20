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
    for (count = 0; count < REPEAT_NUMBER; count++)
    {
        delay_time = (int)(rand() * DELAY_TIME_LEVELS / (RAND_MAX)) + 1;
        sleep(delay_time);
        printf("\t Thread %d: job %d delay = %d.\n", tid, count, delay_time);
    }
    printf("Thread %d finished.\n", tid);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread[THREAD_NUMBER];
    int n, res;
    void *tret;
    srand(time(NULL));
    for (n = 0; n < THREAD_NUMBER; n++)
    {
        res = pthread_create(&thread[n], NULL, (void *)t_fun, (void *)n);
        if (res)
        {
            printf("Thread %d creation failed.\n", n);
            exit(res);
        }
    }
    printf("Thread creation successful.\nWaiting for threads to finish.\n");
    for (n = 0; n < THREAD_NUMBER; n++)
    {
        if (pthread_join(thread[n], &tret))
        {
            printf("Thread %d failed to join.\n", n);
        }
        else
        {
            printf("Thread %d successfully joined.\n", n);
        }
    }
    return 0;
}