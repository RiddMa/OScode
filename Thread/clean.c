/* clean.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *clean(void *arg)
{
    printf("Cleaning up: %s.\n", (char *)arg);
    return (void *)0;
}

void *t_fun1(void *arg)
{
    printf("Thread 1 start.\n");

    pthread_cleanup_push((void *)clean, "Thread1 1st handler");
    pthread_cleanup_push((void *)clean, "Thread1 2nd handler");
    printf("Thread1 completely pushed.\n");
    // 异常终止时清理栈中的函数全部执行
    if (arg)
    {
        return ((void *)1);
    }
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    return ((void *)2);
}

void *t_fun2(void *arg)
{
    printf("Thread 2 start.\n");
    pthread_cleanup_push((void *)clean, "Thread2 1st handler");
    pthread_cleanup_push((void *)clean, "Thread2 2nd handler");
    printf("Thread2 completely pushed.\n");
    if (arg)
    {
        return ((void *)3);
    }
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(0);
    return ((void *)4);
}

int main()
{
    pthread_t tid1, tid2;
    void *tret;
    if (pthread_create(&tid1, NULL, t_fun1, (void *)1))
    {
        printf("Thread creation error.\n");
        return -1;
    }
    if (pthread_create(&tid2, NULL, t_fun2, (void *)0))
    {
        printf("Thread creation error.\n");
        return -1;
    }
    if (pthread_join(tid1, &tret))
    {
        printf("Thread1 join error.\n");
        return -1;
    }
    printf("Thread1 exited with code %d.\n", (int)tret);
    if (pthread_join(tid2, &tret))
    {
        printf("Thread2 join error.\n");
        return -1;
    }
    printf("Thread2 exited with code %d.\n", (int)tret);
    return 0;
}