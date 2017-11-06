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

    if (mSharedMemory->status == WRITTEN_BY_SERVER) {
        printf("Client hasn't read value yet\n");
        exit(-1);
    }

    printf("Enter %d Numbers\n", ARRAY_LENGTH);
    for (i = 0;i < ARRAY_LENGTH;i++) {
        scanf("%d", &mSharedMemory->array[i]);
    }

    mSharedMemory->status = WRITTEN_BY_SERVER;

    if (detach(mSharedMemory) == -1) {
        perror("Error occured while detaching Shared memory\n");
        exit(-1);
    }

    char c;
    printf("Press any key to exit\n");
    scanf(" %c", &c);

}