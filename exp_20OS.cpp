#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;      // controls access to readCount
sem_t wrt;        // ensures mutual exclusion for writers
int readCount = 0; // number of readers currently reading
int data = 0;      // shared resource

void *reader(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);       // lock readCount
        readCount++;
        if (readCount == 1) {
            sem_wait(&wrt);     // first reader locks writers
        }
        sem_post(&mutex);       // unlock readCount

        // critical section: reading
        printf("Reader %d reads data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);       // lock readCount
        readCount--;
        if (readCount == 0) {
            sem_post(&wrt);     // last reader unlocks writers
        }
        sem_post(&mutex);       // unlock readCount

        sleep(1);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&wrt);         // lock writers

        // critical section: writing
        data++;
        printf("Writer %d writes data = %d\n", id, data);
        sleep(2);

        sem_post(&wrt);         // unlock writers

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t r[3], w[2];
    int id_r[3] = {1, 2, 3};
    int id_w[2] = {1, 2};

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // create reader threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&r[i], NULL, reader, &id_r[i]);
    }

    // create writer threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&w[i], NULL, writer, &id_w[i]);
    }

    // join threads (infinite loop, so program runs continuously)
    for (int i = 0; i < 3; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
