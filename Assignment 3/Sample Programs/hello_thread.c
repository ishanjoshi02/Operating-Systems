#include <stdio.h>
#include <pthread.h>

void *print_message(void *argument) {
        char *message = (char *) argument;
        printf("%s\n", message);
        return NULL;
}

int main(int argc, char *argv[]) {
        pthread_t mThread;
        char *argument = "Hello Thread";
        pthread_create(&mThread, NULL, print_message, (void *) argument);
        pthread_join(mThread, NULL);
        return 0; 
}
