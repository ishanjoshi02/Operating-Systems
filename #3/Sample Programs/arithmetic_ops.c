#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arguments {
        int num1, num2;
};

void *add(void *arg) {
        struct arguments *args = (struct arguments *) arg;
        printf("Addition : %d\n", ((*args).num1 + (*args).num2));
        return NULL;
}

void *subtract(void *arg) {
        struct arguments *args = (struct arguments *) arg;
        printf("Subtraction : %d\n", ((*args).num1 - (*args).num2));
        return NULL;
}

void *multiply(void *arg) {
        struct arguments *args = (struct arguments *) arg;
        printf("Multiplication : %d\n", ((*args).num1 * (*args).num2));
        return NULL;
}

void *divide(void *arg) {
        struct arguments *args = (struct arguments *) arg;
        printf("Division : %d\n", ((*args).num1 / (*args).num2));
        return NULL;
}

int main(int argc, char *argv[]) {
        pthread_t mThread[4];
        int i;
        struct arguments args;
        if (argc == 3) {
                args.num1 = atoi(argv[1]);
                args.num2 = atoi(argv[2]);
        } else {
                printf("Enter Two Numbers\n");
                scanf("%d%d", &args.num1, &args.num2);
        }
        pthread_create(&mThread[0], NULL, add, (void *) &args);
        pthread_create(&mThread[1], NULL, subtract, (void *) &args);
        pthread_create(&mThread[2], NULL, multiply, (void *) &args);
        pthread_create(&mThread[3], NULL, divide, (void *) &args);
        
        for (i = 0;i < 4;i++) {
                pthread_join(mThread[i], NULL);
        }
        return 0;
}
