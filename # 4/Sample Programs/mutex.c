// Write a Program using Mutex and Pthread, where Thread_1 writes information into Shared Variable and Thread_2 reads Information from
// that Shared Data
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int data = -209;

void *read(void *arg) {

	// Convert Passed argument to pthread_mutex_t type
	pthread_mutex_t *mutex = (pthread_mutex_t *) arg;
	
	// Get Lock on Mutex
	pthread_mutex_lock(mutex);
	
	// Simple Check to confirm that the Writer has provided value in Data variable
	if (data == -209) {
		printf("Writer has not provided value\n");
		return NULL;
	} 
	
	// Print Value saved in data variable
	printf("Value entered by the writer is %d\n\n", data);
	
	// Remove Lock on Mutex
	pthread_mutex_unlock(mutex);
	
	return NULL;

}

void *write(void *arg) {

	// Convert Passed argument to pthread_mutex_t type
	pthread_mutex_t *mutex = (pthread_mutex_t *) arg;
	
	// Get Lock on Mutex
	pthread_mutex_lock(mutex);
	
	// Take Input from User and Save value in data variable
	printf("Enter an Integer\n");
	scanf("%d", &data);
	 
	// Remove Lock on Mutex
	pthread_mutex_unlock(mutex);
	
	return NULL;

}

int main(int argc, char **argv) {
	
	// Declaring Mutex Variable
	pthread_mutex_t mMutex = PTHREAD_MUTEX_INITIALIZER;
	
	// Declaring Threads to execute read and write functions
	pthread_t write_thread, read_thread;
	
	int cont;
	
	while(1) {
	
		// Creating both the Threads
		pthread_create(&write_thread, NULL, write, (void *) &mMutex);
		pthread_create(&read_thread, NULL, read, (void *) &mMutex);
		
		// Waiting for both the Threads to join Main Thread
		pthread_join(write_thread, NULL);
		pthread_join(read_thread, NULL);
		
		printf("Do you want to continue writing and reading data\nEnter 1 to Continue\n");
		scanf("%d", &cont);
		
		if (cont == 1) {
			
			// Setting Data back to original value i.e. -209
			data = -209;
				
		} else {
		
			// Exiting Program
			exit(0);
			
		}
	}		
	
	return 0;
	
}
