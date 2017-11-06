#include <sys/ipc.h>
#include <sys/shm.h>

#define PROJECT_ID 209

#define READ_BY_CLIENT 0
#define WRITTEN_BY_SERVER 1

#define ARRAY_LENGTH 3

// Status holds either value READ_BY_CLIENT or WRITTEN_BY_SERVER
// Server writes into an array of ARRAY_LENGTH and the client reads this
typedef struct SharedMemory {
    int status;
    int array[ARRAY_LENGTH];
}SharedMemory;

key_t getKey() {
    return ftok(".", PROJECT_ID);
}

int shm_init() {
    return shmget(getKey(), sizeof(SharedMemory), IPC_CREAT | 0666);
}

SharedMemory *attach(int shm_id) {
    return (SharedMemory *) shmat(shm_id, NULL, 0);
}

int detach(SharedMemory *shm) {
    return shmdt((void *) shm);
}