#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 5
#define SIZE 5

sem_t empty, full;
int buffer[SIZE]; /* shared data structure */
/* mutual exclusion lock for critical section access */
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    int i;
    for (i = 0; i < MAX; ++i) {
        printf("Producing item %d\n", i);
        sem_wait(&empty);   // wait until empty is not 0
        pthread_mutex_lock(&mtx);
        buffer[i] = i;           // put the produced item into the buffer
        printf("Item placed in buffer.\n");
    pthread_mutex_unlock(&mtx);
        sem_post(&full);      // increase full by 1
    }
    return NULL;
}

void *consumer(void *arg) {
    int j;
    for (j = 0; j < MAX; ++j) {
        sem_wait(&full);     // wait until full is not 0
        pthread_mutex_lock(&mtx);
        printf("Consuming item %d\n", buffer[j]);
        buffer[j] = -1;       // remove the consumed item from the buffer
        printf("Item removed from buffer.\n");
        pthread_mutex_unlock(&mtx);
        sem_post(&empty);    // decrease empty by 1
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    srand((unsigned) time(NULL));
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    if (pthread_create(&prod, NULL, producer, NULL)) {
        perror("Failed to create producer thread.");
        exit(-1);
    }
    if (pthread_create(&cons, NULL, consumer, NULL)) {
        perror("Failed to create consumer thread.");
        exit(-2);
    }
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    return 0;
}
    
