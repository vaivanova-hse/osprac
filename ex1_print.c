#include <stdio.h>
#include "stdlib.h"
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>


int main() {
    // Descriptor.
    int shmid;
    int file_size = 0;
    int *array;
    // IPC key.
    key_t key;
    char *file_text;
    // For key generation.
    char pathname[] = "ex1_print.c";

    // Key generation.
    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    // Open shared memory for key.
    if ((shmid = shmget(key, sizeof(int) + file_size * sizeof(char), 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t open or find shared memory\n");
        exit(-1);
    }


    // Try to map.
    if ((array = (int *) shmat(shmid, NULL, 0)) == (int *) (-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    file_size = *array;
    file_text = (char *) (array + 1);

    for (int i = 0; i < file_size; i++) {
        putchar(file_text[i]);
    }

    if (shmdt(file_size_ptr) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) < 0) {
        printf("Can't delete shared memory\n");
        exit(-1);
    }

    return 0;
}