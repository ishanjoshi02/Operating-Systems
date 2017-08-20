#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct arg_struct {
  int rows, cols;
  int **a;
  int **b;
};
void acceptArray(int **a, int rows, int cols) {
  int i, j;
  for (i = 0;i < rows;i++)
    for (j = 0;j < cols;j++)
      scanf("%d", (*(a+i)+j));
}
int **allocateMemory(int rows, int cols) {
  int i;
  int **a = (int **) malloc(sizeof(int *) * rows);
  for (i = 0;i < rows;i++)
    *(a + i) = (int *) malloc(sizeof(int) * cols);
  return a;
}
void printArray(int **a, int rows, int cols) {
  int i, j;
  for (i = 0;i < rows;i++) {
      for (j = 0;j < cols;j++) {
        printf("%d\t", *(*(a+i)+j));
      }
      printf("\n");
  }
}
void multiplyArray(void *arguments) {
  struct arg_struct *args = (struct arg_struct*) arguments;
  int rows = (* args).rows;
  int cols = (* args).cols;
  int **a = (* args).a;
  int **b = (* args).b;
  int i, j, k, **c;
  c = allocateMemory(rows, cols);
  for (i = 0;i < rows;i++)
    for (j = 0;j < cols;j++) {
      *(*(c + i) + j) = 0;
      for (k = 0;k < cols;k++)
        *(*(c + i) + j) += *(*(a + i) + k) + *(*(b + k) + j);
    }
  printArray(c, rows, cols);
}
int main() {
  int rows, cols, **a, **b;
  printf("Enter the Number of Rows and Columns in the 2-D Arrays\n");
  scanf("%d%d", &rows, &cols);
  a = allocateMemory(rows, cols);
  b = allocateMemory(rows, cols);
  printf("Enter Elements of Array 1\n");
  acceptArray(a, rows, cols);
  printf("Enter Elements of Array 2\n");
  acceptArray(b, rows, cols);
  pthread_t thread;
  struct arg_struct *args;
  (* args).rows = rows;
  (* args).cols = cols;
  (* args).a = a;
  (* args).b = b;
  int ret = pthread_create(&thread, NULL, multiplyArray, (void*)(args));
  if (ret) {
    printf("Error - Thread Creation Failed\nError Code: %d\n", ret);
    exit(EXIT_FAILURE);
  }
  pthread_join(thread, NULL);
  exit(EXIT_SUCCESS);
}
