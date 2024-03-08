#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <string.h>
#include <errno.h>

#define SHARED_MEMORY_KEY 1234
#define SHARED_MEMORY_SIZE 100

int main() {
    int shmid;
    char *shared_memory;

    shmid = shmget(SHARED_MEMORY_KEY, sizeof(char) * SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shared_memory = (char *) shmat(shmid, NULL, 0);
    if (shared_memory == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    strncpy(shared_memory, "Hello, shared memory!", SHARED_MEMORY_SIZE - 1);
    shared_memory[SHARED_MEMORY_SIZE - 1] = '\0'; 

    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    printf("Data written to shared memory.\n");

    return 0;
}

