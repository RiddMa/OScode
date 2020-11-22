/* asmbly_line_t.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int countA;
int countB;
int countEmpty;
pthread_mutex_t mutex;
sem_t mutexA;
sem_t mutexB;
sem_t mutexStation;
sem_t suspendA;
sem_t suspendB;
sem_t suspendC;

void *workerA(void *)
{
    while (1)
    {
        sleep(1);
        sem_wait(&mutexA);
        sem_wait(&mutexStation);
        pthread_mutex_lock(&mutex);
        if (countA <= 7 && countEmpty >= 2)
        {
            countA = countA + 2;
            countEmpty = countEmpty - 2;
            printf("WorkerA: Station +2A,\t\tStation got %d A(s) now.\n", countA);
            pthread_mutex_unlock(&mutex);
            sem_post(&mutexStation);
            sem_post(&mutexA);
            sem_post(&suspendC);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            sem_post(&mutexStation);
            sem_post(&mutexA);
            sem_wait(&suspendA);
        }
    }
}

void *workerB(void *)
{
    while (1)
    {
        sleep(1);
        sem_wait(&mutexB);
        sem_wait(&mutexStation);
        pthread_mutex_lock(&mutex);
        if (countB <= 7 && countEmpty >= 1)
        {
            countB = countB + 1;
            countEmpty = countEmpty - 1;
            printf("WorkerB: Station +1B,\t\tStation got %d B(s) now.\n", countB);
            pthread_mutex_unlock(&mutex);
            sem_post(&mutexStation);
            sem_post(&mutexB);
            sem_post(&suspendC);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            sem_post(&mutexStation);
            sem_post(&mutexB);
            sem_wait(&suspendB);
        }
    }
}

void *workerC(void *)
{
    while (1)
    {
        sleep(1);
        sem_wait(&mutexA);
        sem_wait(&mutexB);
        pthread_mutex_lock(&mutex);
        if (countA >= 4 && countB >= 3)
        {
            sem_wait(&mutexStation);
            countA = countA - 4;
            countB = countB - 3;
            countEmpty = countEmpty + 7;
            printf("WorkerC: Station -4A -3B,\tStation got %d A(s) and %d B(s) now.\n", countA, countB);
            pthread_mutex_unlock(&mutex);
            sem_post(&mutexStation);
            sem_post(&mutexB);
            sem_post(&mutexA);
            sem_post(&suspendA);
            sem_post(&suspendB);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            sem_post(&mutexB);
            sem_post(&mutexA);
            sem_wait(&suspendC);
        }
    }
}

int main(int argc, char *argv[])
{
    pthread_t A_id, B_id, C_id;

    countA = 0;
    countB = 0;
    countEmpty = 12;

    pthread_mutex_init(&mutex, NULL);

    int ret = sem_init(&mutexStation, 0, 1);
    if (ret)
    {
        printf("sem init mutexStation error.\n");
        exit(0);
    }

    ret = sem_init(&mutexA, 0, 1);
    if (ret)
    {
        printf("sem init mutexA error\n");
        exit(0);
    }

    ret = sem_init(&mutexB, 0, 1);
    if (ret)
    {
        printf("sem init mutexB error.\n");
        exit(0);
    }

    ret = sem_init(&suspendA, 0, 0);
    if (ret)
    {
        printf("sem init suspendA error.\n");
        exit(0);
    }

    ret = sem_init(&suspendB, 0, 0);
    if (ret)
    {
        printf("sem init suspendB error.\n");
        exit(0);
    }

    ret = sem_init(&suspendC, 0, 0);
    if (ret)
    {
        printf("sem init suspendC error.\n");
        exit(0);
    }

    ret = pthread_create(&A_id, NULL, workerA, NULL);
    if (ret)
    {
        printf("create workerA failed.\n");
        exit(0);
    }

    ret = pthread_create(&B_id, NULL, workerB, NULL);
    if (ret)
    {
        printf("create workerB failed.\n");
        exit(0);
    }

    ret = pthread_create(&C_id, NULL, workerC, NULL);
    if (ret)
    {
        printf("create workerC failed.\n");
        exit(0);
    }

    pthread_join(A_id, NULL);
    pthread_join(B_id, NULL);
    pthread_join(C_id, NULL);

    exit(0);
}