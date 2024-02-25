#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024
struct SharedData {
    int counter;
};
int main() {
    int shmId;
    pid_t pid;
    struct SharedData *sharedData;
    shmId = shmget(IPC_PRIVATE, sizeof(struct SharedData), IPC_CREAT | 0666);
    if (shmId < 0) {
        perror("shmget");
        exit(1);
    }
    sharedData = (struct SharedData *)shmat(shmId, NULL, 0);
    if ((intptr_t)sharedData == -1) {
        perror("shmat");
        exit(1);
    }
    sharedData->counter = 0;
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) { 
        for (int i = 0; i < 5; i++) {
            sleep(1); 
            sharedData->counter++;
            printf("Child: Counter = %d\n", sharedData->counter);
        }
    } else {
        wait(NULL);
        printf("Parent: Counter = %d\n", sharedData->counter);
        shmdt((void *)sharedData);
        shmctl(shmId, IPC_RMID, NULL);
    }
    return 0;
}

