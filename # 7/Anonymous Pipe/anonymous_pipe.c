#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define SZ 4096

int main(int argc, char *argv[]) {

    int pipefd[2], pipefd1[2];
    pid_t pid;
    FILE *fp;

    if ((pipe(pipefd) == -1) || (pipe(pipefd1) == -1)) {

        perror("Error occured while creating Pipes\nExiting\n");
        exit(-1);

    }

    if ((pid = fork()) == -1) {

        perror("Error occured while creating Child Process\nExiting\n");
        exit(-1);

    } else if (pid == 0) {

        // This is the Child Process

        // Closing Write Buffer of Pipe 1
        close(pipefd[1]);

        char filePath[100];

        // Reading pointer to the file stored in the Buffer and assign it to fp
        read(pipefd[0], filePath, sizeof(filePath));

        char readBuffer[1000];
        int i = 0;

        // Opening the File to write on it
        if ((fp = fopen(filePath, "r")) == NULL) {

            printf("Error occured while creating file at '%s'\n", filePath);
            exit(-1);

        }

        while (!feof(fp)) {
            readBuffer[i++] = fgetc(fp);
        }
        
        fclose(fp);

        // Now writing Contents of File to Write Buffer of second pipe
        close(pipefd1[0]); // Closing Read Buffer of the Pipe

        write(pipefd1[1], readBuffer, sizeof(readBuffer));

        // Closing Write Buffer of Second Pipe
        close(pipefd1[1]);

    } else {

        // This is the Parent Process

        // Closing Reader part of Pipe 1
        close(pipefd[0]);

        char filePath[100];
        printf("Enter the Path of the File\n");
        scanf("%s", filePath);


        // Write Pointer to the File in the Write Buffer of the Pipe
        write(pipefd[1], filePath, sizeof(filePath));
        // Close Writer Buffer of the Pipe
        close(pipefd[1]);

        // Wait for Child Process to complete its execution
        wait(NULL);

        // Closing Write Buffer of the Second Pipe
        close(pipefd1[1]);

        char readBuffer[100];

        // Reading Contents stored in the Buffer
        read(pipefd1[0], readBuffer, sizeof(readBuffer));

        close(pipefd1[0]); // Closing Read Buffer of the Second Pipe

        fprintf(stdout, "Contents of the File are\n%s\n", readBuffer);

    }

    return 0;

}
