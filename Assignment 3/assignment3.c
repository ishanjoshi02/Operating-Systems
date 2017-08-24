#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct args {
  int i, j;
  int rows, cols;
  int **a, **b, **c;
}args;
void log(char *message) {
  printf("%s\n", message);
}
int **allocateMemory(int rows, int cols) {
  int **a = (int **) malloc(sizeof(int *) * rows);
  int i;
  for (i = 0;i < cols;i++)
    *(a + i) = (int *) malloc(sizeof(int) * cols);
  return a;
}
int **accept(int rows, int cols) {
  int **a;
  a = allocateMemory(rows, cols);
  int i, j;
  for (i = 0;i < rows;i++)
    for(j = 0;j < cols;j++)
      scanf("%d", (*(a + i) + j));
  return a;
}
void display(int **a, int rows, int cols) {
  int i, j;
  for(i = 0;i < rows;i++) {
      for(j = 0;j < cols;j++)
        printf("%d\t", *(*(a + i) + j));
      printf("\n");
  }
}
void threadFunc(void *args) {
  struct args *arguments = (struct args *) args;
  int k;
  *(*((* arguments).c + (* arguments).i) + (* arguments).j) = 0;
  for (k = 0;k < (* arguments).cols;k++) {
    *(*((* arguments).c + (* arguments).i) + (* arguments).j) +=
    *(*((* arguments).a + (* arguments).i) + k) *
    *(*((* arguments).b + k) + (* arguments).j);
  }
  pthread_exit(NULL);
}
int main() {
  int i, j;
  int rows, cols;
  int **a, **b, **c;
  int numberOfThreads;
  pthread_t *mThreads;
  printf("Enter the Number of Rows and Columns\n");
  scanf("%d%d",&rows,&cols);
  printf("Enter Elements of Array 1\n");
  a = accept(rows, cols);
  printf("Enter Elements of Array 2\n");
  b = accept(rows, cols);
  c = allocateMemory(rows, cols);
  numberOfThreads = 0;
  mThreads = (pthread_t *) malloc(sizeof(pthread_t) * (rows * cols));
  for (i = 0;i < rows;i++) {
    for (j = 0;j < cols;j++) {
      struct args *arguments = (struct args *) malloc(sizeof(struct args));
      (* arguments).rows = rows;
      (* arguments).cols = cols;
      (* arguments).a = a;
      (* arguments).b = b;
      (* arguments).c = c;
      (* arguments).i = i;
      (* arguments).j = j;
      pthread_create(&mThreads[numberOfThreads++], NULL, threadFunc, (void *) arguments);
    }
  }
  for (j = 0;j < numberOfThreads;j++) {
    pthread_join(mThreads[j], NULL);
  }
  display(c, rows, cols);
  return 0;
}
