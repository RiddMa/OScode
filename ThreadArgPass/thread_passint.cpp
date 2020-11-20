#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *mythread(void *i)
{
    int *num;
    num = (int *)i;
    printf("The parameter is %d.\n", *num);
    return NULL;
}

int main(int argc, const char *argv[])
{
    int ret = 0;
    pthread_t id;
    int test = 233;
    int *temp = &test;

    if (pthread_create(&id, NULL, mythread, (void *)temp))
    {
        printf("Create error.\n");
        return 1;
    }
    printf("The thread is created by ridd.\n");
    pthread_join(id, NULL);
    
    return 0;
}