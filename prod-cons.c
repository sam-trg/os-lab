#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0; // Number of items in the buffer
sem_t empty;   // Count of empty slots
sem_t full;    // Count of full slots
pthread_mutex_t mutex; // Mutex for critical section

void* producer(void* arg) {
    int producerId = *((int*)arg);
    while (1) {
        int item = rand() % 100; // Produce a random item

        sem_wait(&empty); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Add item to buffer
        buffer[count++] = item;
        printf("Producer %d produced %d\n", producerId, item);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full); // Signal that a new item is available

        sleep(rand() % 2); // Sleep for a bit
    }
}

void* consumer(void* arg) {
    int consumerId = *((int*)arg);
    while (1) {
        sem_wait(&full); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Remove item from buffer
        int item = buffer[--count];
        printf("Consumer %d consumed %d\n", consumerId, item);

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty); // Signal that a new slot is available

        sleep(rand() % 2); // Sleep for a bit
    }
}

int main() {
    pthread_t producers[3], consumers[3];
    int producerIds[3], consumerIds[3];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // All slots are empty initially
    sem_init(&full, 0, 0);             // No full slots initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    for (int i = 0; i < 3; i++) {
        producerIds[i] = i + 1;
        consumerIds[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producerIds[i]);
        pthread_create(&consumers[i], NULL, consumer, &consumerIds[i]);
    }

    // Join threads (optional in an infinite loop)
    for (int i = 0; i < 3; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    // Clean up (this code won't be reached)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
