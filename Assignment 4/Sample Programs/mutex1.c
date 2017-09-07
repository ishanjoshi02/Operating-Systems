// Write a Program using Mutex and Pthread, where Thread_1 writes information into File and Thread_2 reads Information from
// that File
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

FILE *file = NULL;

void *read(void *arg) {

	// Convert Passed argument to pthread_mutex_t type
	pthread_mutex_t *mutex = (pthread_mutex_t *) arg;
	
	// string variable will be used to store data retrieved from the file
	char *string = (char *) malloc(sizeof(char) * 100);
	
	// Get Lock on Mutex
	pthread_mutex_lock(mutex);
	
	file = fopen("temp.txt", "r");
	if (file == NULL) {
		printf("No Data entered by the Writer\n");
		return NULL;
	} else {
		fscanf(file, "%s", string);
	} 	
	
	printf("Data Entered in the File is \n%s\n", string);
	
	// Closing File
	fclose(file);
	
	// Remove Lock on Mutex
	pthread_mutex_unlock(mutex);
	
	return NULL;

}

void *write(void *arg) {

	// Convert Passed argument to pthread_mutex_t type
	pthread_mutex_t *mutex = (pthread_mutex_t *) arg;

	// string variable will be used to store data inputted by the user
	char *string = (char *) malloc(sizeof(char) * 100);
	
	// Get Lock on Mutex
	pthread_mutex_lock(mutex);
	
	// Take Input from User and Save value in data variable
	printf("Enter a String\n");
	scanf("%s", string);
	
	// Opening File
	file = fopen("temp.txt", "w+");
	if (file == NULL) {
		printf("File Couldn't be created\n");
		return NULL;
	} else {
		fprintf(file, "%s", string);
	}
	
	// Closing File
	fclose(file); 
	 
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
		
		
		// Setting Data back to original value i.e. -209
		remove("temp.txt");
		
		if (cont != 1) {
		
			// Exiting Program
			exit(0);
			
		}
	}		
	
	return 0;
	
}
