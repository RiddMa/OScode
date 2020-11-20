/* create.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread1(void)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("I'm the 1st thread.\n");
        sleep(1);
    }
}

void *thread2(void)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("I'm the 2nd thread.\n");
        sleep(1);
    }
}

int main()
{
    pthread_t id1, id2;
    int res;
    if (pthread_create(&id1, NULL, (void *)thread1, NULL) != 0)
    {
        printf("pthread1 creation error.\n");
        return -1;
    }
    if (pthread_create(&id2, NULL, (void *)thread2, NULL) != 0)
    {
        printf("pthread2 creation error.\n");
        return -1;
    }

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    return 0;
}