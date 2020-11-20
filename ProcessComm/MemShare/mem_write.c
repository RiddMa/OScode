/* mem_write.c */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

typedef struct
{
    char name[8];
    int age;
} people;

int main(int argc, char **argv)
{
    int shm_id, i;
    key_t key;
    char tmp[8];
    people *p_map;
    char pathname[30];
    strcpy(pathname, "/tmp");
    key = ftok(pathname, 0x03); //create key using ftok()
    if (key == -1)
    {
        perror("ftok error.\n");
        return -1;
    }
    printf("key = %d.\n", key);
    //shm_id is identifier for shared memory
    //shmget() create shared memory
    shm_id = shmget(key, 4096, IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id == -1)
    {
        perror("shmget error.\n");
        return -1;
    }
    printf("shm_id = %d.\n", shm_id);
    //map shared memory
    p_map = (people *)shmat(shm_id, NULL, 0);
    memset(tmp, 0x00, sizeof(tmp));
    strcpy(tmp, "test");
    tmp[4] = '0';
    for (i = 0; i < 3; i++)
    {
        tmp[4] += 1;
        strncpy((p_map + 1)->name, tmp, 5);
        (p_map + i)->age = 0 + i;
    }
    //detach shared memory address to
    //prevent process from accessing this block of memory.
    shmdt(p_map);
    return 0;
}