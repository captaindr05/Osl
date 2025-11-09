#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

pthread_mutex_t mutex;
sem_t empty, full;

void *producer(void *arg)
{
    int id = *(int *)arg;
    int item;
    for (int i = 1; i <= 5; i++) // each produces 5 items
    {
        item = i;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d produced %d\n", id, item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int id = *(int *)arg;
    int item;
    for (int i = 1; i <= 5; i++) // each consumes 5 items
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer %d consumed %d\n", id, item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main()
{
    int np, nc;
    printf("Enter number of producers: ");
    scanf("%d", &np);
    printf("Enter number of consumers: ");
    scanf("%d", &nc);

    pthread_t prod[np], cons[nc];
    int pid[np], cid[nc];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for (int i = 0; i < np; i++)
    {
        pid[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &pid[i]);
    }
    for (int i = 0; i < nc; i++)
    {
        cid[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cid[i]);
    }

    for (int i = 0; i < np; i++)
        pthread_join(prod[i], NULL);
    for (int i = 0; i < nc; i++)
        pthread_join(cons[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}

