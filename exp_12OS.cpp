#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5   // number of philosophers

sem_t chopstick[N];
sem_t room;    // to allow at most N-1 philosophers to avoid deadlock

void *philosopher(void *num) {
    int id = *(int *)num;

    // each philosopher tries to eat only once for simplicity
    sem_wait(&room);  // enter room (max N-1 philosophers)
    printf("Philosopher %d has entered room\n", id);

    sem_wait(&chopstick[id]);             // pick left chopstick
    sem_wait(&chopstick[(id + 1) % N]);   // pick right chopstick

    printf("Philosopher %d is eating\n", id);
    sleep(2);  // simulate eating

    printf("Philosopher %d has finished eating\n", id);

    sem_post(&chopstick[(id + 1) % N]);   // put right chopstick
    sem_post(&chopstick[id]);             // put left chopstick

    sem_post(&room);  // leave room
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[N];
    int ids[N];

    // initialize semaphores
    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    // create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        if (pthread_create(&tid[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    // wait for all to finish
    for (int i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    // destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }
    sem_destroy(&room);

    return 0;
}
