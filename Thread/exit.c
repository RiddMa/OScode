/* exit.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *create(void *argc)
{
    printf("A new thread created.\n");
    pthread_exit((void *)233);
}

int main()
{
    pthread_t tid;
    void *tmp;
    printf("I'm the main thread.\n");
    if (pthread_create(&tid, NULL, create, NULL) != 0)
    {
        printf("pthread creation error.\n");
        return -1;
    }
    if (pthread_join(tid, &tmp) != 0)
    {
        printf("pthread did not exit.\n");
        return -2;
    }
    printf("pthread exit code returned %d.\n", (int)tmp);
    return 0;
}