#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

typedef struct {

  int buffer;
  sem_t full, empty;

}Shared;

Shared sh;

void *producer(void *argp) {

  int i, item;

  for (i = 0;i < BUFFER_SIZE;i++) {

    sem_wait(&sh.empty);

    item = rand();
    printf("Produced: %d\n", item);

    sh.buffer = item;

    sem_post(&sh.full);

  }

  return NULL;

}

void *consumer(void *argc) {

  int i, item;
  for (i = 0;i < BUFFER_SIZE;i++) {

    sem_wait(&sh.full);

    item = sh.buffer;

    printf("Consumed: %d\n", item);
    sem_post(&sh.empty);


  }

  return NULL;

}

int main(int argc, char const *argv[]) {

  pthread_t ptid, ctid;

  sem_init(&sh.empty, 0, 1);
  sem_init(&sh.full, 0, 0);

  pthread_create(&ptid, NULL, producer, NULL);
  pthread_create(&ctid, NULL, consumer, NULL);

  pthread_join(ptid, NULL);
  pthread_join(ctid, NULL);

  return 0;
}
