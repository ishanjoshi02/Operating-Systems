
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_number(void *argument) {
        int *number = (int *) argument;
        printf("%d\n", *number);        
        return NULL;
}

int main(int argc, char *argv[]) {
        pthread_t mThread;
        int number;
        if (argc == 2) {
                number = atoi(argv[1]);
        } else {
                printf("Enter an Integer\n");
                scanf("%d", &number);
        }
        pthread_create(&mThread, NULL, print_number, (void *) &number);
        pthread_join(mThread, NULL);
        return 0; 
}
