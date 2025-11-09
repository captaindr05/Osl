#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1024

int main()
{
    key_t key;
    int shmid;
    char *shm;

    key = ftok("shmfile",65);                /* generate unique key */
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if(shmid < 0){ perror("shmget"); exit(1); }

    shm = (char*) shmat(shmid, NULL, 0);     /* attach */
    if(shm == (char*) -1){ perror("shmat"); exit(1); }

    printf("Enter message to write in shared memory:\n");
    if(fgets(shm, SHM_SIZE, stdin) == NULL) shm[0] = '\0';

    printf("Data written in memory: %s\n", shm);

    shmdt(shm);                              /* detach (keep segment) */
    return 0;
}

