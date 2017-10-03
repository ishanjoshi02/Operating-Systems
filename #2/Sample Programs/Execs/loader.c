#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *arguments[argc + 1];
  char *executable = "simple_add";
  int i;
  if (argc < 2) {
    printf("Too Few Arguments\n");
    exit(1);
  }
  for (i = 0;i <= argc;i++) {
    arguments[i] = (char *) malloc(sizeof(char) * 10);
  }
  arguments[0] = executable;
  arguments[argc + 1] = (char *) 0;
  for (i = 1;i <= argc;i++) {
    arguments[i] = argv[i];
  }
  execv(executable, arguments);
  return 0;
}
