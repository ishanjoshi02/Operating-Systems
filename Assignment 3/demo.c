#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *demo(void *arg) {
	printf("Hello World\n");
	return NULL;
}

int main() {
	pthread_t *thread = (pthread_t *) malloc(sizeof(pthread_t));
	pthread_create(thread, NULL, demo, NULL);
	pthread_join(*thread, NULL);
	return 0;
}
