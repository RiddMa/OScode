#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static int a = 5;

void *mythread(void *i)
{
    int *num;
    num = (int *)i;
    printf("The parameter is: %d\n", *num);
    return NULL;
}

int main(int argc, const char *argv[])
{
    pthread_t id1, id2;
    int *tmp = &a;

    if (pthread_create(&id1, NULL, mythread, (void *)tmp))
    {
        printf("Create error.\n");
        return -1;
    }
    printf("The thread is created by ridd.\n");
    a = 10;
    if (pthread_create(&id2, NULL, mythread, (void *)tmp))
    {
        printf("Create error.\n");
        return -1;
    }
    printf("The thread is created by ridd.\n");
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    
    return 0;
}