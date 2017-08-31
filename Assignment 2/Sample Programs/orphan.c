#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    system("clear");
    pid_t pid = fork();
    if (pid == 0) {
      int i;
      pid_t startPpid = getppid();
      for (i = 0;i < 10000;i++) {
        pid_t newPpid = getppid();
        if (startPpid != newPpid) {
          printf("Child Orphaned!\nNew Parent Process Id is : %ld\n", (long) newPpid);
          startPpid = newPpid;
        }
      }
    } else { }
    return 0;
}
