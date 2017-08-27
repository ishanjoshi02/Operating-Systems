#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("Too Few Arguments\n");
    exit(1);
  }
  int *array, sum = 0;
  int i;
  array = (int *) malloc(sizeof(int) * argc);
  for (i = 1;i < argc;i++) {
    *(array + i - 1) = atoi(argv[i]);
  }
  for (i = 0;i < argc;i++) {
    sum += *(array + i);
  }
  printf("%d\n", sum);
  return 0;
}
