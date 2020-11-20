#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct msg_st
{
    long int msg_type;
    char text[MAX_TEXT];
};

int main()
{
    int running = 1;
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;

    //create msg queue
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d.\n", errno);
        exit(EXIT_FAILURE);
    }

    //send msg to queue until "end"
    while (running)
    {
        //input data
        printf("Enter some text:\n");
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 1;
        strcpy(data.text, buffer);
        //write msg to queue
        if (msgsnd(msgid, (void *)&data, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed.\n");
            exit(EXIT_FAILURE);
        }
        //finish input when input "end"
        if (strncmp(buffer, "end", 3) == 0)
        {
            running = 0;
        }
        sleep(1);
    }
    exit(EXIT_SUCCESS);
}