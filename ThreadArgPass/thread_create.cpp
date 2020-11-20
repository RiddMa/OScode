#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *mythread1(void *)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("This is the 1st pthread, created by ridd.\n");
        sleep(1);
    }
    return NULL;
}

void *mythread2(void *)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("This is the 2nd pthread, created by ridd.\n");
        sleep(1);
    }
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t id1, id2;

    if (pthread_create(&id1, NULL, mythread1, NULL))
    {
        printf("Create error.\n");
        return 1;
    }
    if (pthread_create(&id2, NULL, mythread2, NULL))
    {
        printf("Create error.\n");
        return 1;
    }

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    return 0;
}