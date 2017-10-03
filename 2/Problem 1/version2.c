// Sorting using Merge Sorts

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
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
