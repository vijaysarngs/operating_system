#include <stdio.h>
#include <pthread.h>
void *threadFunction1(void *arg) {
    printf("Thread 1 says: Hello from Thread 1!\n");
    pthread_exit(NULL);
}
void *threadFunction2(void *arg) {
    printf("Thread 2 says: Hello from Thread 2!\n");
    pthread_exit(NULL);
}
int main() {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, threadFunction1, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1.\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, threadFunction2, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2.\n");
        return 1;
    }
    if (pthread_join(thread1, NULL) != 0) {
        fprintf(stderr, "Error joining thread 1.\n");
        return 1;
    }
    if (pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "Error joining thread 2.\n");
        return 1;
    }
    printf("Main thread says: Threads have completed their execution.\n");
    return 0;
}

