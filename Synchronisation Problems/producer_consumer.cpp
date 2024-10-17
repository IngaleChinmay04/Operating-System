#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE]; // Critical section
int in = 0, out = 0;

// Semaphore
sem_t empty_slots;
sem_t full;
pthread_mutex_t mutex; // to protect the critical section   

void *producer(void *arg)
{
    int item;
    while (true)
    {
        item = rand() % 100;    // generate random number
        sem_wait(&empty_slots); // Wait until there's an empty_slots slot
        pthread_mutex_lock(&mutex);

        // add item
        buffer[in] = item;
        cout << "Producer produced " << item << endl;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // increment full semaphore
        sleep(1);
    }
}

void *consumer(void *arg)
{
    int item;
    while (true)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        cout << "Consumer consumed: " << item << endl;
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty_slots);

        sleep(1);
    }
}

int main()
{
    pthread_t prod, cons;

    // initialize
    sem_init(&empty_slots, 0, BUFFER_SIZE); // initially all buffer empty_slots
    sem_init(&full, 0, 0);                  // Initially no full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}