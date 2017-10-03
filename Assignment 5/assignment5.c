#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 1024

int fdr, fdw;

char input_buffer[SIZE];
char output_buffer[SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *arg) {

  int ret_val;
  int n;
  pthread_mutex_lock(&mutex);

  fdr = open("file.txt", O_RDONLY);

  while (n = read(fdr, output_buffer, SIZE) > 0) {

    printf("Reader: %s\n", output_buffer);

  }

  printf("\n");
  close(fdr);
  pthread_mutex_unlock(&mutex);
  system("rm -f file.txt");

}
void *writer(void *arg) {

  pthread_mutex_lock(&mutex);

  fdw = open("file.txt", O_CREAT | O_WRONLY);
  printf("Writer:\n");
  gets(input_buffer);
  write(fdw, input_buffer, strlen(input_buffer));
  close(fdw);

  pthread_mutex_unlock(&mutex);

}

int main(int argc, char const *argv[]) {

  pthread_t rd_tid;
  pthread_t wr_tid;

  while (1) {

    pthread_create(&wr_tid, NULL, writer, NULL);
    pthread_create(&rd_tid, NULL, reader, NULL);

    pthread_join(wr_tid, NULL);
    pthread_join(rd_tid, NULL);

  }

  return 0;
}
