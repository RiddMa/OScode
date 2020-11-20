#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *mythread(void *str)
{
        char *s;
        s = (char *)str;
        printf("The string parameter is: %s.\n", s);
        return NULL;
}

int main(int argc, const char *argv[])
{
        pthread_t id;
        char test[] = "Hello World!";
        char *temp = test;

        if (pthread_create(&id, NULL, mythread, (void *)temp))
        {
                printf("Create error.\n");
                return 1;
        }

        printf("The thread is created by ridd.\n");
        pthread_join(id, NULL);
        
        return 0;
}