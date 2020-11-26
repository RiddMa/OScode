/* asmbly_line.c */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/mman.h>
#define KEY (key_t)14010322

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *arry;
};

static void semaphore_p(int sem_id, int semNum);
static void semaphore_v(int sem_id, int semNum);

int main(int argc, char *argv[])
{
    //set some counts to record the numbers of A, B and empty on the station
    int *countA;
    int *countB;
    int *countEmpty;
    countA = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    countB = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    countEmpty = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *countA = 0;
    *countB = 0;
    *countEmpty = 12;

    //create six semaphores using semget
    int semid;
    if ((semid = semget(KEY, 6, IPC_CREAT | 0660)) == -1)
    {
        printf("semget error.\n");
        return -1;
    }

    //init six semaphores using semctl
    union semun arg[6];
    arg[0].val = 1; //mutexA = 1
    arg[1].val = 1; //mutexB = 1
    arg[2].val = 1; //mutexStation = 1
    arg[3].val = 0; //suspendA = 0
    arg[4].val = 0; //suspendB = 0
    arg[5].val = 0; //suspendC = 0

    int i;
    for (i = 0; i < 6; i++)
    {
        semctl(semid, i, SETVAL, arg[i]);
    }

    //create processes for workerA, workerB and workerC
    pid_t p1, p2;

    //worker A
    if ((p1 = fork()) == 0)
    {
        while (1)
        {
            semaphore_p(semid, 0);
            semaphore_p(semid, 2);
            if (*countEmpty >= 2 && *countA <= 7)
            {
                *countEmpty = *countEmpty - 2;
                *countA = *countA + 2;
                printf("WorkerA: Station +2A,\t\tStation got %d A(s) now.\n", *countA);
                if (*countA >= 4 && semctl(semid, 5, GETVAL, NULL) < 1)
                {
                    semaphore_v(semid, 5);
                }
                semaphore_v(semid, 2);
                semaphore_v(semid, 0);
            }
            else
            {
                semaphore_v(semid, 2);
                semaphore_v(semid, 0);
                semaphore_p(semid, 3);
            }
            sleep(1);
        }
        //workerB
    }
    else if ((p2 = fork()) == 0)
    {
        while (1)
        {
            semaphore_p(semid, 1);
            semaphore_p(semid, 2);
            if (*countEmpty >= 1 && *countB <= 7)
            {
                *countEmpty = *countEmpty - 1;
                *countB = *countB + 1;
                printf("WorkerB: Station +1B,\t\tStation got %d B(s) now.\n", *countB);
                if (*countB >= 3 && semctl(semid, 5, GETVAL, NULL) < 1)
                {
                    semaphore_v(semid, 5);
                }
                semaphore_v(semid, 2);
                semaphore_v(semid, 1);
            }
            else
            {
                semaphore_v(semid, 2);
                semaphore_v(semid, 1);
                semaphore_p(semid, 4);
            }
            sleep(1);
        }
    }
    else //workerC
    {
        while (1)
        {
            semaphore_p(semid, 0);
            semaphore_p(semid, 1);
            if (*countA >= 4 && *countB >= 3)
            {
                semaphore_p(semid, 2);
                *countA = *countA - 4;
                *countB = *countB - 3;
                *countEmpty = *countEmpty + 7;
                printf("WorkerC: Station -4A -3B,\tStation got %d A(s) and %d B(s) now.\n", *countA, *countB);
                semaphore_v(semid, 2);
                semaphore_v(semid, 1);
                semaphore_v(semid, 0);
                semaphore_v(semid, 3);
                semaphore_v(semid, 4);
            }
            else
            {
                semaphore_v(semid, 1);
                semaphore_v(semid, 0);
                semaphore_p(semid, 5);
            }
            //sleep(1);
        }
    }
}

//wait
void semaphore_p(int sem_id, int semNum)
{
    struct sembuf sem_b;
    sem_b.sem_num = semNum;
    sem_b.sem_op = -1;
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "%d semaphore_p failed\n", semNum);
        return;
    }
    return;
}

//signal
void semaphore_v(int sem_id, int semNum)
{
    struct sembuf sem_b;
    sem_b.sem_num = semNum;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    if (semNum == 5)
        printf("%d\n", semctl(sem_id, semNum, GETVAL, NULL));
    if (semop(sem_id, &sem_b, 1) == -1)
    {
        fprintf(stderr, "%d,%d,semaphore_v failed\n", semctl(sem_id, semNum, GETVAL, NULL), semNum);
        return;
    }
    return;
}