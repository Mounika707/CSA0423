#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_INCREMENTS 1000

int counter = 0;               // shared resource
pthread_mutex_t lock;          // mutex lock

void* increment(void* arg) {
    int i;
    for (i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&lock);   // acquire lock
        counter++;                   // critical section
        pthread_mutex_unlock(&lock); // release lock
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    // initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed!\n");
        return 1;
    }

    // create threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    // wait for threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // destroy mutex
    pthread_mutex_destroy(&lock);

    printf("Final counter value: %d\n", counter);

    return 0;
}
