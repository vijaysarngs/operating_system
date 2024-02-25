#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct Message {
    long messageType;
    char text[100];
};
int main() {
    key_t key;
    int msgQueueID;
    if ((key = ftok("msgQueueExample", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }
    if ((msgQueueID = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    pid_t childPID = fork();
    if (childPID == -1) {
        perror("fork");
        exit(1);
    }
    if (childPID > 0) {
        struct Message message;
        message.messageType = 1;
        sprintf(message.text, "Hello from the parent!");

        if (msgsnd(msgQueueID, &message, sizeof(message.text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        wait(NULL);
    }
    else {
        struct Message receivedMessage;
        if (msgrcv(msgQueueID, &receivedMessage, sizeof(receivedMessage.text), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("Child Process received message: %s\n", receivedMessage.text);
    }
    if (msgctl(msgQueueID, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    return 0;
}

