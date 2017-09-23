#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

#define proj_id 209

#define LENGTH 3

#define READ_BY_CLIENT 0
#define WRITTEN_BY_SERVER 1

typedef struct SharedMemory {

  int status;
  int array[LENGTH];

}SharedMemory;

key_t getKey() {

  return ftok(".", proj_id);

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


void write() {

  int i;

  // Initialising Shared Memory
  int shm_id;

  // Checking if Initialising Shared Memory has thrown an error or not
  if ((shm_id = shm_init()) == -1) {

    perror("Error occured while creating Shared Memory\n");
    exit(-1);

  }

  // Initialising Structure (SharedMemory) and attaching Shared Memory to the Process's Memory Space
  SharedMemory *mSharedMemory = attach(shm_id);

  // Checking if Client has read data from Shared Memory
  if (mSharedMemory->status == WRITTEN_BY_SERVER) {

    printf("Array not read by the Client Process\nExiting\n");
    exit(0);

  }

  printf("Enter %d Numbers\n", LENGTH);
  for (i = 0;i < LENGTH;i++) {

    scanf("%d", &mSharedMemory->array[i]);

  }

  // Setting Status of Structure (SharedMemory) to WRITTEN_BY_SERVER

  mSharedMemory->status = WRITTEN_BY_SERVER;

  if (detach(mSharedMemory) == -1) {

    perror("Error occured while detaching Shared Memory from Process's Memory Space\n");
    exit(-1);

  }

  char c;
  printf("Press any key to exit\n");
  scanf(" %c", &c);

}

void read() {

  int i;

  // Initialising Shared Memory
  int shm_id;

  // Checking if Initialising Shared Memory has thrown an error or not
  if ((shm_id = shm_init()) == -1) {

    perror("Error occured while creating Shared Memory\n");
    exit(-1);

  }

  // Initialising Structure (SharedMemory) and attaching Shared Memory to the Process's Memory Space
  SharedMemory *mSharedMemory = attach(shm_id);

  // Checking if Client has read data from Shared Memory
  if (mSharedMemory->status == READ_BY_CLIENT) {

    printf("Array not written by the Client Process\nExiting\n");
    exit(0);

  }

  printf("Numbers entered by the Servers are\n");
  for (i = 0;i < LENGTH;i++) {

    printf("%d\n", mSharedMemory->array[i]);

  }

  // Setting Status of Structure (SharedMemory) to WRITTEN_BY_SERVER

  mSharedMemory->status = READ_BY_CLIENT;

  if (detach(mSharedMemory) == -1) {

    perror("Error occured while detaching Shared Memory from Process's Memory Space\n");
    exit(-1);

  }

}

int main(int argc, char *argv[]) {


  int choice;

  if (argc == 2) {

    if (argv[1] == "-w") {

      choice = 2;

    } else {

      choice = 1;

    }

  } else {

    printf("Do you want to \n1. Read\n2. Write\n");
    scanf("%d", &choice);

  }

  if (choice == 1) {

    read();

  } else {

    write();

  }

  return 0;
}
