#include <stdio.h>
#include "stdlib.h"
#include <errno.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>


int main() {
    int shmid;
    int *array;
    int file_size = 0;
    char pathname[] = "ex1_print.c";
    key_t key;
    FILE *file;

    // Getting size of the file for ok shared memory writing.
    file = fopen(pathname, "r");
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, sizeof(int) + file_size * sizeof(char), 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t create or find shared memory\n");
        exit(-1);
    }

    if ((array = (int *) shmat(shmid, NULL, 0)) == (int *) (-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    *file_size_ptr = file_size;
    char *file_text;
    file_text = (char *) (array + 1);

    // Writing.
    for (int i = 0; i < file_size; i++) {
        file_text[i] = fgetc(file);
    }
    fclose(file);

    if (shmdt(file_size_ptr) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}