#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
       printf("In Child Process\n");     
       exit(0);
    }
    else {
        system("ps");
        sleep(50);
        printf("In Parent Process\n");    
    }
    return 0;
}
