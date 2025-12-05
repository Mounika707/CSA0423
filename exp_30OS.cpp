#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// -------- Thread Functions --------
void* threadCreateFunc(void* arg) {
    printf("Hello from the created thread!\n");
    return NULL;
}

void* threadJoinFunc(void* arg) {
    printf("Thread is running...\n");
    return (void*)"Thread result from join demo";
}

void* threadEqualFunc(void* arg) {
    pthread_t tid = pthread_self();
    // Print thread ID safely
    printf("Thread running with ID: %lu\n", (unsigned long)tid);
    return NULL;
}

void* threadExitFunc(void* arg) {
    printf("Thread is exiting...\n");
    pthread_exit((void*)"Goodbye from thread (exit demo)");
}

// -------- Main Program --------
int main() {
    int choice;
    pthread_t tid1, tid2;
    void* result;

    printf("Thread Demonstration Program\n");
    printf("1. Create\n");
    printf("2. Join\n");
    printf("3. Equal\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Create
            if (pthread_create(&tid1, NULL, threadCreateFunc, NULL) != 0) {
                perror("pthread_create failed");
                return 1;
            }
            pthread_join(tid1, NULL);
            printf("Main thread finished (Create demo).\n");
            break;

        case 2: // Join
            pthread_create(&tid1, NULL, threadJoinFunc, NULL);
            pthread_join(tid1, &result);
            printf("Thread joined. Returned: %s\n", (char*)result);
            break;

        case 3: // Equal
            pthread_create(&tid1, NULL, threadEqualFunc, NULL);
            pthread_create(&tid2, NULL, threadEqualFunc, NULL);
            pthread_join(tid1, NULL);
            pthread_join(tid2, NULL);
            if (pthread_equal(tid1, tid2)) {
                printf("Threads are equal.\n");
            } else {
                printf("Threads are NOT equal.\n");
            }
            break;

        case 4: // Exit
            pthread_create(&tid1, NULL, threadExitFunc, NULL);
            pthread_join(tid1, &result);
            printf("Thread exited with message: %s\n", (char*)result);
            break;

        default:
            printf("Invalid choice.\n");
    }

    return 0;
}
