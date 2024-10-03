#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t wrt;
pthread_mutex_t mutex;
int read_count = 0;
int value = 0; // shared resource

void *writer(void *arg)
{
    while (true)
    {
        sem_wait(&wrt);

        // critical section to write
        value++;
        cout << "Write wrote value: " << value << endl;

        sem_post(&wrt); // release semaphore
        sleep(1);
    }
    return NULL;
}

void *reader(void *arg)
{
    while (true)
    {
        pthread_mutex_lock(&mutex); // mutual exclusion for read count
        read_count++;
        if (read_count == 1)
        {
            sem_wait(&wrt); // even if one reader, lock the semaphore
        }
        pthread_mutex_unlock(&mutex); // release mutex after read count
        cout << "Reader read value: " << value << endl;

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0)
        {
            sem_post(&wrt); // last reader unlocks writer semaphore
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t readers[3], writers[3];

    // Initialize the semaphores and mutex
    sem_init(&wrt, 0, 1);             // Writer semaphore initialized to 1
    pthread_mutex_init(&mutex, NULL); // Mutex initialized

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&writers[i], NULL, writer, NULL);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&readers[i], NULL, reader, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(writers[i], NULL);
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}