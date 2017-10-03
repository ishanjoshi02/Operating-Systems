#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
  int size, *array;
  int i;
  pid_t pid;
  printf("Enter the Size of the Array\n");
  scanf("%d", &size);
  array = (int *) malloc(sizeof(int) * size);
  printf("Enter the Elements of the Array\n");
  for (i = 0;i < size;i++) {
    scanf("%d", (array + i));
  }
  pid = fork();
  if (pid == 0) {

  } else {
    
  }
  return 0;
}
