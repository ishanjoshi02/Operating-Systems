#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define item_in 10
#define item_out 100
#define ctid_length 3

int item_in_array[item_in], item_out_array[item_out];
int item_in_count = 0, item_out_count = 0;
int no = 0;

pthread_t ptid, ctid[ctid_length], disp_tid;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t full, empty;

void swap(int *a, int *b) {

  int temp = *a;
  *a = *b;
  *b = temp;

}

void sort() {

  int i, j;

  for (i = 0;i < no;i++) {

    for (j = 0;j < (no - i);j++) {

      if (item_out_array[j] > item_out_array[j + 1]) {

        swap(&item_out_array[j], &item_out_array[j + 1]);

      }

    }

  }

}

void *disp_output(void *var) {

  int i;
  while (1) {

    sort();
    for (i = 0;i < no;i++) {

      printf("[%d]\n", item_out_array[i]);
      sleep(3);

    }

  }

}

void add_item(int item) {

  int i = 0;
  if (no == 0) {

    item_out_array[no] = item;

  } else {

    item_out_array[--i] = item;

  }

  no++;

}

void *producer(void *var) {

  int item;

  while (1) {

    item = rand();
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    if (item_in_count < item_in) {

      item_in_array[item_in_count] = item;
      item_in_count++;

    }

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    sleep(1);

  }

  return NULL;

}

void *consumer(void *var) {

  int item;

  while (1) {

    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    if (item_in_count > 0) {

      add_item(item_in_array[--item_in_count]);

    }

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    sleep(1);

  }

  return NULL;

}

int main(int argc, char const *argv[]) {

  int i;

  sem_init(&empty, 0, 10);
  sem_init(&full, 0, 0);

  pthread_create(&ptid, NULL, producer, NULL);

  for (i = 0;i < ctid_length;i++) {

    pthread_create(&ctid[i], NULL, consumer, NULL);

  }

  pthread_create(&disp_tid, NULL, disp_output, NULL);

  pthread_join(ptid, NULL);

  for (i = 0; i < ctid_length;i++) {

    pthread_join(ctid[i], NULL);

  }

  pthread_join(disp_tid, NULL);

  return 0;

}
