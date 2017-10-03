#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arguments {
        int a, b;
};

void *print_sum(void *args) {
        struct arguments *mArguments = (struct arguments *) args;
        return (void *) ((*mArguments).a + (*mArguments).b);
}

int main(int argc, char *argv[]) {
        pthread_t mThread;
        struct arguments args;
        void *return_val;
        if (argc == 3) {
                args.a = atoi(argv[1]);
                args.b = atoi(argv[2]);
        } else {
                printf("Enter two Numbers\n");
                scanf("%d%d", &args.a, &args.b);
        }
        pthread_create(&mThread, NULL, print_sum, (void *) &args);
        pthread_join(mThread, return_val);
        int *answer = (int *) return_val;
        printf("%d\n", *answer);
        return 0;
}
