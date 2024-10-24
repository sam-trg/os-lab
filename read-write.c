#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 5 // Size of the bounded buffer
#define NUM_READERS 5
#define NUM_WRITERS 3

sem_t writeBlock;         // Semaphore for writers
sem_t mutex;              // Mutex for the critical section
int readCount = 0;        // Number of active readers

// Bounded buffer
int buffer[MAX_BUFFER_SIZE];
int count = 0;            // Number of items in the buffer

void* reader(void* arg) {
    int readerNum = *((int*)arg);

    while (1) {
        // Entry section for readers
        sem_wait(&mutex);
        readCount++;
        if (readCount == 1)
            sem_wait(&writeBlock); // Block writers if first reader
        sem_post(&mutex);

        // Reading section
        printf("Reader %d is reading\n", readerNum);
        sleep(1); // Simulate reading time

        // Exit section for readers
        sem_wait(&mutex);
        readCount--;
        if (readCount == 0)
            sem_post(&writeBlock); // Release writers if last reader
        sem_post(&mutex);

        sleep(1); // Simulate some time before next read
    }
}

void* writer(void* arg) {
    int writerNum = *((int*)arg);

    while (1) {
        // Entry section for writers
        sem_wait(&writeBlock); // Block readers and other writers

        // Writing section
        if (count < MAX_BUFFER_SIZE) { // Check for space in the buffer
            buffer[count] = rand() % 100; // Simulate writing
            printf("Writer %d wrote %d\n", writerNum, buffer[count]);
            count++;
            sleep(1); // Simulate writing time
        }

        // Exit section for writers
        sem_post(&writeBlock); // Allow readers and other writers
        sleep(2); // Simulate some time before next write
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIds[NUM_READERS], writerIds[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&writeBlock, 0, 1); // Binary semaphore for writers
    sem_init(&mutex, 0, 1);       // Mutex for critical section

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Join threads (this is optional for an infinite loop)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores (this code will never reach here in this infinite loop)
    sem_destroy(&writeBlock);
    sem_destroy(&mutex);

    return 0;
}
