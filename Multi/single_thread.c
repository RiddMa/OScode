/* single_thread.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

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

int main(int argc, const char *argv[])
{
    apple test0;
    orange test1;
    long int runtimeQueue_us[M];

    int sum, i, j;
    struct timeval tv_begin, tv_end;

    for (j = 0; j < M; j++)
    {
        gettimeofday(&tv_begin, NULL);
        for (sum = 0; sum < APPLE_MAX_VALUE; sum++)
        {
            test0.a += sum;
            test0.b += sum;
        }

        sum = 0;
        for (i = 0; i < ORANGE_MAX_VALUE; i++)
        {
            sum += test1.a[i] + test1.b[i];
        }
        gettimeofday(&tv_end, NULL);
        runtimeQueue_us[j] = 1000000 * (tv_end.tv_sec - tv_begin.tv_sec) + tv_end.tv_usec - tv_begin.tv_usec;
        printf("%d : %ld\n", j, runtimeQueue_us[j]);
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