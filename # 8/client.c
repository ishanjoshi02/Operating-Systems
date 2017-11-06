#include <stdio.h>
#include <stdlib.h>
#include "SharedMemory.c"

int main() {
    int shm_id, i;
    if ((shm_id = shm_init()) == -1) {
        perror("Error occured while initialising Shared Memory\n");
        exit(-1);
    }

    SharedMemory *mSharedMemory = attach(shm_id);

    if (mSharedMemory->status == READ_BY_CLIENT) {
        printf("Server hasn't written value yet\n");
        exit(-1);
    }

    printf("Printing %d Numbers\n", ARRAY_LENGTH);
    for (i = 0;i < ARRAY_LENGTH;i++) {
        printf("%d\n", mSharedMemory->array[i]);
    }

    mSharedMemory->status = READ_BY_CLIENT;

    if (detach(mSharedMemory) == -1) {
        perror("Error occured while detaching Shared memory\n");
        exit(-1);
    }

}