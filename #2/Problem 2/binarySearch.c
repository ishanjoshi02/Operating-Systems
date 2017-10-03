#include <stdio.h>
#include <stdlib.h>

// Delete sort and swap function after testing binary search
void swap(int *i, int *j) {
  int temp = *i;
  *i = *j;
  *j = temp;
}
int sort(int *array, int size) {
  int i, j;
  for (i = 0;i < size - 1;i++)
    for (j = 0;j < size - i - 1;j++)
      if (*(array + j) < *(array + j + 1))
        swap((array + j), (array +  j + 1));
}

int binarySearch(int array[], int key, int start, int end) {
  while (start <= end) {
    int m = start + (end - start)/2;
    if (array[m] == key)
        return m;
    if (array[m] < key)
        start = m + 1;
    else 
        end = m - 1;
    }
    return -1;
}

int main(int argc, char *argv[], char *argp[]) {
  int *array, size, key;
  int i;
  printf("Enter the Size of the Array\n");
  scanf("%d", &size);
  array = (int *) malloc(sizeof(int) * size);
  printf("Enter the Elements of the Array\n");
  for (i = 0;i < size;i++)
    scanf("%d", (array + i));
  sort(array, size);      
  printf("Enter the Value to be Searched\n");
  scanf("%d", &key);
  int index = binarySearch(array, key, 0, size - 1);
  if (index == -1)
    printf("Value not Found\n");
  else
    printf("Value found at %d position\n", index);
  return 0;
}
