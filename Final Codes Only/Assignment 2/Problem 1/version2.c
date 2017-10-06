// Sorting using Merge Sorts

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
//Quick sort
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
void quicksortInc(int array[], int low, int high) {
 
  if (low < high) {
    int pi = partitionInc(array, low, high);
    quicksortInc(array, low, pi - 1);
    quicksortInc(array, pi + 1, high);
  }
}
void quicksortDec(int array[], int low, int high) {
  if (low < high) {
    int pi = partitionDec(array, low, high);
    quicksortDec(array, low, pi - 1);
    quicksortDec(array, pi + 1, high);
  }
}
//Merge Sort
void mergeInc(int array[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  int L[n1], R[n2];
  for (i = 0;i < n1;i++) {
    L[i] = array[l + i];
  }
  for (j = 0;j < n2;j++) {
    R[j] = array[m + 1 + j];
  }
  i = 0;j = 0;k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      array[k] = L[i++];
    } else {
      array[k] = R[j++];
    }
    k++;
  }
  while (i < n1)
    array[k++] = L[i++];
  while (j < n2)
    array[k++] = R[j++];
}
void mergeDec(int array[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  int L[n1], R[n2];
  for (i = 0;i < n1;i++) {
    L[i] = array[l + i];
  }
  for (j = 0;j < n2;j++) {
    R[j] = array[m + 1 + j];
  }
  i = 0;j = 0;k = l;
  while (i < n1 && j < n2) {
    if (L[i] >= R[j]) {
      array[k] = L[i++];
    } else {
      array[k] = R[j++];
    }
    k++;
  }
  while (i < n1)
    array[k++] = L[i++];
  while (j < n2)
    array[k++] = R[j++];
}
void sortInc(int array[], int start, int end) {
  
  if (start < end) {
    int m = start + (end - start)/2;
    sortInc(array, start, m);
    sortInc(array, m + 1, end);
    mergeInc(array, start, m , end);
  }
}
void sortDec(int array[], int start, int end) {
  if (start < end) {
    int m = start + (end - start)/2;
    sortDec(array, start, m);
    sortDec(array, m + 1, end);
    mergeDec(array, start, m , end);
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
  {
  printf("\n Child-----quick sort\n");
    quicksortInc(array, 0, size - 1);    //call to quick sort
    }  
  else {
    wait(NULL);
    printf("\n Parent-----merge sort\n");
    sortInc(array, 0, size - 1);    //call to merge sort
  }
  printf("Sorted Array:\n");
  for(i = 0;i < size;i++)
    printf("%d\t", *(array + i));
  printf("\n");
  return 0;
}
