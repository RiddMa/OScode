#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>

#define ORANGE_MAX_VALUE 1000000
#define APPLE_MAX_VALUE 100000000
#define MSECOND 1000000
#define K 10
#define M 200
#define epsilon 0.02

typedef struct apple
{
    unsigned long long a;
    unsigned long long b;
} apple;

typedef struct orange
{
    int a[ORANGE_MAX_VALUE];
    int b[ORANGE_MAX_VALUE];
} orange;

pthread_mutex_t mutex;

void sort(long int *arr, int arrlen)
{
    int i, j;
    for (i = 1; i < arrlen; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (arr[i] < arr[j])
            {
                long int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

void *compute_apple_a(void *test)
{
    apple *t = (apple *)test;
    int sum;

    pthread_mutex_lock(&mutex);
    for (sum = 0; sum < APPLE_MAX_VALUE; sum++)
    {
        //pthread_mutex_lock(&mutex);
        t->a += sum;
        //pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&mutex);

    printf("apple a thread ends.\n");
}

void *compute_apple_b(void *test)
{
    apple *t = (apple *)test;
    int sum;

    pthread_mutex_lock(&mutex);
    for (sum = 0; sum < APPLE_MAX_VALUE; sum++)
    {
        //pthread_mutex_lock(&mutex);
        t->b += sum;
        //pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
    printf("apple b thread ends.\n");
}

void *compute_orange(void *test)
{
    orange *t = (orange *)test;
    int sum, i;

    sum = 0;
    for (i = 0; i < ORANGE_MAX_VALUE; i++)
    {
        sum += t->a[i] + t->b[i];
    }

    printf("orange thread ends.\n");
}

int main(int argc, const char *argv[])
{
    //code here
    apple apple;
    orange orange;
    pthread_t id0, id1, id2;
    //K-path
    long int runtime;
    long int runtimeQueue_us[M];

    int i;
    int ret;
    struct timeval tv_begin, tv_end;

    for (i = 0; i < M; i++)
    {
        gettimeofday(&tv_begin, NULL);
        ret = pthread_create(&id0, NULL, compute_apple_a, (void *)&apple);
        if (ret)
        {
            perror("apple a thread error!");
        }
        ret = pthread_create(&id1, NULL, compute_orange, (void *)&orange);
        if (ret)
        {
            perror("orange thread error!");
        }
        ret = pthread_create(&id2, NULL, compute_apple_b, (void *)&apple);
        if (ret)
        {
            perror("apple b thread error!");
        }

        pthread_join(id0, NULL);
        pthread_join(id1, NULL);
        pthread_join(id2, NULL);
        gettimeofday(&tv_end, NULL);
        runtimeQueue_us[i] = 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec;
        printf("%d : %ld\n", i, 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec);
    }
    sort(runtimeQueue_us, M);
    for (i = 0; i < K; i++)
    {
        printf("%ld", runtimeQueue_us[i]);
        if (i == K - 1)
            printf("\n");
        else
        {
            printf(",");
        }
    }
    if ((double)runtimeQueue_us[0] * (1 + epsilon) >= (double)runtimeQueue_us[K - 1])
    {
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }

    return 0;
}