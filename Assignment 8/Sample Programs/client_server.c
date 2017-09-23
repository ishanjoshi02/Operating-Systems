#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SIZE 4096
#define proj_id 209

void println(char *string) {

	printf("%s\n", string);

}

void mRead() {

	char *message;
	// Creating/Fetching Shared Memory Space
	int shm_id = shmget(ftok(".", proj_id), SIZE, IPC_CREAT | 0666);
	
	if (shm_id == -1) {
	
		println("Shared Memory Error");
		exit(-1);
	
	} else {
	
		// Attaching Shared Memory Space to Process Memory Space
		char *message = (char *) shmat(shm_id, NULL, 0);
		
		if (strlen(message) == 0) {
		
			println("No Message Entered by the Server");		
			return;
		
		} else {
		
			printf("Message entered by Server is %s\n", message); 	
		
		}
		
		// Detaching Shared Memory from Process Memory Space
		if (shmdt((void *) message) == -1) {
		
			println("Error detaching Shared Memory");
			exit(-1);
		
		}
		
		int choice;
		
		println("Do you want to Destroy Shared Memory Space");
		println("1. Yes");
		println("2. No");
		
		scanf("%d", &choice);
		
		if (choice == 1) {
		
			shmctl(shm_id, IPC_RMID, NULL);
		
		}
		
	}

}

void mWrite() {

	char *message;
	// Creating/Fetching Shared Memory Space
	int shm_id = shmget(ftok(".", proj_id), SIZE, IPC_CREAT | 0666);
	
	if (shm_id == -1) {
	
		println("Shared Memory Error");
		exit(-1);
	
	} else {
	
		// Attaching Shared Memory Space to Process Memory Space
		char *message = (char *) shmat(shm_id, NULL, 0);
		
		println("Please enter a Message to send to the Client");
		scanf("%s", message);
		
		// Detaching Shared Memory from Process Memory Space
		if (shmdt((void *) message) == -1) {
		
			println("Error detaching Shared Memory");
			exit(-1);
		
		} else {
		
			int choice;
			
			println("Do you want to Exit");
			scanf("%d", &choice);
		
		}
	
	}

}

int main(int argc, char* argv[]) {

	if (argc == 2) {
	
		if (argv[1] == "write") {
		
			mWrite();
		
		} else if (argv[1] == "read") {
			
			mRead();
		
		}
	
	} else {
		
		int choice;
		println("Do you want to");
		println("1. Write");
		println("2. Read");
		scanf("%d", &choice);
		
		if (choice == 1) {
		
			mWrite();
		
		} else if (choice == 2) {
		
			mRead();
		
		}
		
	}	

}
