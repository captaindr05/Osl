#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    // Use same key to access the segment
    key_t key = ftok("shmfile", 65);
    // Get the already-created shared memory
    int shmid = shmget(key, 1024, 0666);

    // Attach it to client’s address space
    char *str = (char*) shmat(shmid, NULL, 0);

    // Read and display the message
    printf("Message read from shared memory:\n%s\n", str);

    // Detach and remove shared memory
    shmdt(str);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

