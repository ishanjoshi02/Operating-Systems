// Sorting using Bubble Sort

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
void sortInc(int array[], int n) {
  int i, j;
  for (i = 0;i < n-1;i++)
    for (j = 0;j < n-i-1;j++)
      if (array[j] < array[j+1])
        swap(&array[j], &array[j+1]);
}
void sortDec(int array[], int n) {
  int i, j;
  for (i = 0;i < n-1;i++)
    for (j = 0;j < n-i-1;j++)
      if (array[j] > array[j+1])
        swap(&array[j], &array[j+1]);
}
int main() {
  int size, i, *array;
  printf("Enter the Size of the Array\n");
  scanf("%d", &size);
  array = (int*) malloc(size * sizeof(int));
  printf("Enter the Elements of the Array\n");
  for (i = 0;i < size;i++)
    scanf("%d", (array+i));
  pid_t pid = fork();
  if (pid == 0)
    sortInc(array, size);
  else {
      wait(NULL);
      sortDec(array, size);
  }
  printf("Sorted Array:\n");
  for(i = 0;i < size;i++)
    printf("%d\t", *(array + i));
  printf("\n");
  return 0;
}
