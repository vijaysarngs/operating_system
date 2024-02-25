#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Error creating child process");
        exit(1);
    }
    if (child_pid != 0) {
        printf("Parent process ID (PID): %d\n", getpid());
        printf("Child process ID (PID): %d\n", child_pid);
    } else {
        printf("Child process ID (PID): %d\n", getpid());
    }
    return 0;
}
