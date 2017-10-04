#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Struct args is used to bundle the code into one variable,
// since, in pthread_create, we can only pass one variable of void * type

struct args {
  int i, j;
  int rows, cols;
  int **a, **b, **c;
}args;
void log(char *message) {

  // This is a simple function that will help in debugging the Code

  printf("%s\n", message);
}

// Allocate space to array of rows number of Rows and cols number of Columns

int **allocateMemory(int rows, int cols) {
  int **a = (int **) malloc(BUFFER_SIZEof(int *) * rows);
  int i;
  for (i = 0;i < cols;i++)
    *(a + i) = (int *) malloc(BUFFER_SIZEof(int) * cols);
  return a;
}

// A function that accepts an array of rows Rows and cols Columns

int **accept(int rows, int cols) {
  int **a;
  a = allocateMemory(rows, cols);
  int i, j;
  for (i = 0;i < rows;i++)
    for(j = 0;j < cols;j++)
      scanf("%d", (*(a + i) + j));
  return a;
}

// Display function to print an array

void display(int **a, int rows, int cols) {
  int i, j;
  for(i = 0;i < rows;i++) {
      for(j = 0;j < cols;j++)
        printf("%d\t", *(*(a + i) + j));
      printf("\n");
  }
}

// threadFunc is the function we pass to pthread_create. This thread calculates the value of each element of the resultant matrix

void threadFunc(void *args) {
  struct args *arguments = (struct args *) args;
  int k;
  *(*((* arguments).c + (* arguments).i) + (* arguments).j) = 0;
  for (k = 0;k < (* arguments).cols;k++) {
    *(*((* arguments).c + (* arguments).i) + (* arguments).j) +=
    *(*((* arguments).a + (* arguments).i) + k) *
    *(*((* arguments).b + k) + (* arguments).j);
  }

  // Explicit call to exit from Thread

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
  mThreads = (pthread_t *) malloc(BUFFER_SIZEof(pthread_t) * (rows * cols));
  for (i = 0;i < rows;i++) {
    for (j = 0;j < cols;j++) {

      // Bundling all the variables into one struct type variable.

      struct args *arguments = (struct args *) malloc(BUFFER_SIZEof(struct args));
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

  // pthread_join waits for the passed threads to complete their execution

  for (j = 0;j < numberOfThreads;j++) {
    pthread_join(mThreads[j], NULL);
  }
  display(c, rows, cols);
  return 0;
}
