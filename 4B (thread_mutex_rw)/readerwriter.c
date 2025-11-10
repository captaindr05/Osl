#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Mutexes
pthread_mutex_t x, wsem;

// Counters
int readcount = 0;

// Function prototypes
void* reader(void* param);
void* writer(void* param);

void initialize()
{
    pthread_mutex_init(&x, NULL);
    pthread_mutex_init(&wsem, NULL);
}

void* reader(void* param)
{
    int waittime = rand() % 5 + 1;  // Random read time (1-5 sec)

    printf("\nReader is trying to enter");
    
    pthread_mutex_lock(&x);
    readcount++;
    if(readcount == 1)
        pthread_mutex_lock(&wsem); // First reader locks writers
    printf("\n\tReader %d is inside", readcount);
    pthread_mutex_unlock(&x);

    sleep(waittime);  // Simulate reading

    pthread_mutex_lock(&x);
    printf("\n\tReader %d is leaving", readcount);
    readcount--;
    if(readcount == 0)
        pthread_mutex_unlock(&wsem); // Last reader unlocks writers
    pthread_mutex_unlock(&x);

    pthread_exit(0);
}

void* writer(void* param)
{
    int waittime = rand() % 3 + 1; // Random write time (1-3 sec)
    static int writer_id = 0;

    pthread_mutex_lock(&wsem);
    writer_id++;
    printf("\nWriter %d has entered", writer_id);

    sleep(waittime);  // Simulate writing

    printf("\nWriter %d is leaving", writer_id);
    pthread_mutex_unlock(&wsem);

    pthread_exit(0);
}

int main()
{
    int n_readers, n_writers, i;

    printf("\nReader/Writer Problem with Reader Priority\n");
    printf("Enter the number of readers: ");
    scanf("%d", &n_readers);
    printf("Enter the number of writers: ");
    scanf("%d", &n_writers);

    pthread_t readers[n_readers], writers[n_writers];

    initialize();

    // Create reader threads
    for(i = 0; i < n_readers; i++)
        pthread_create(&readers[i], NULL, reader, NULL);

    // Create writer threads
    for(i = 0; i < n_writers; i++)
        pthread_create(&writers[i], NULL, writer, NULL);

    // Join reader threads
    for(i = 0; i < n_readers; i++)
        pthread_join(readers[i], NULL);

    // Join writer threads
    for(i = 0; i < n_writers; i++)
        pthread_join(writers[i], NULL);

    printf("\nAll readers and writers have finished.\n");
    return 0;
}

