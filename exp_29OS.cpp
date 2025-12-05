#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores and mutex
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

// Producer function
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = i + 1; // produce item

        sem_wait(&empty);              // wait for empty slot
        pthread_mutex_lock(&mutex);    // lock buffer

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // unlock buffer
        sem_post(&full);               // signal full slot

        sleep(1); // simulate time
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);               // wait for full slot
        pthread_mutex_lock(&mutex);    // lock buffer

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);  // unlock buffer
        sem_post(&empty);              // signal empty slot

        sleep(2); // simulate time
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
