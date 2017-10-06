//Sorting using Quick Sort

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void log(char* message) { printf("%s\n", message); }
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
int partitionInc(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);
  int j;
  for (j = low;j <= high - 1;j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}
int partitionDec(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);
  int j;
  for (j = low;j <= high - 1;j++) {
    if (arr[j] >= pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}
void sortInc(int array[], int low, int high) {
  if (low < high) {
    int pi = partitionInc(array, low, high);
    sortInc(array, low, pi - 1);
    sortInc(array, pi + 1, high);
  }
}
void sortDec(int array[], int low, int high) {
  if (low < high) {
    int pi = partitionDec(array, low, high);
    sortDec(array, low, pi - 1);
    sortDec(array, pi + 1, high);
  }
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
    sortInc(array, 0, size - 1);
  else {
    wait(NULL);
    sortDec(array, 0, size - 1);
  }
  printf("Sorted Array:\n");
  for(i = 0;i < size;i++)
    printf("%d\t", *(array + i));
  printf("\n");
  return 0;
}
