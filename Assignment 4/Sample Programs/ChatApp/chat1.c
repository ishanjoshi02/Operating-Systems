#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>

#define SIZE 4096
#define proj_id1 29
#define proj_id2 209

void println(char *message) {

  printf("%s\n", message);

}

void *mRead(void *arg) {

  char *message;

  int shm_id = shmget(ftok(".", proj_id1), SIZE, IPC_CREAT | 0666);

  if (shm_id == -1) {

    println("Error");
    exit(-1);

  } else {

    char *message = (char *) shmat(shm_id, NULL, 0);

		if (strlen(message) != 0) {

        printf("%s\n", message);

    }
    if (shmdt((void *) message) == -1) {

			// println("Error detaching Shared Memory");
			// exit(-1);

		}

    shmctl(shm_id, IPC_RMID, NULL);

  }

}

void *mWrite(void *arg) {

  char *user_name = (char *) arg;
  char *message;

  int shm_id = shmget(ftok(".", proj_id2), SIZE, IPC_CREAT | 0666);

  if (shm_id == -1) {

    println("Error");
    exit(-1);

  } else {

    char *message = (char *) shmat(shm_id, NULL, 0);

    char *temp = (char *) malloc(sizeof(char) * 100);

    scanf("%s", temp);

    message = strcat(user_name, temp);

    if (shmdt((void *) message) == -1) {

      println("Error detaching Shared Memory\nW");
      exit(-1);

    }

  }

}

int main() {

  char *user_name = (char *) malloc(sizeof(char) * 100);

  println("Please Enter Your Name");
  scanf("%s", user_name);

  pthread_t writer, reader;

  while (1) {

    pthread_create(&writer, NULL, mWrite, (void *) user_name);
    pthread_create(&reader, NULL, mRead, NULL);

    pthread_join(writer, NULL);
    pthread_join(reader, NULL);

  }

}
