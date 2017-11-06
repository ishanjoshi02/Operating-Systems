#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t readCountAccess;
sem_t databaseAccess;
int readCount = 0;

void *Reader(void *args) {

    sleep(1);
    int temp = (int) args;
    printf("Reader %d is trying to enter into database for reading the data\n", temp);
    sem_wait(&readCountAccess);
    readCount++;
    if (readCount == 1) {
        sem_wait(&databaseAccess);
        printf("Reader %d is reading the database\n", temp);
    }

    sem_post(&readCountAccess);
    sem_wait(&readCountAccess);

    readCount--;
    if (readCount == 0) {

        printf("Reader %d is leaving the database\n", temp);
        sem_post(&databaseAccess);

    }

    sem_post(&readCountAccess);

}

void *Writer(void *args) {

    sleep(1);
    int temp = (int) args;
    printf("Writer %d is trying to enter into database for modifying the data\n", temp);
    sem_wait(&databaseAccess);
    printf("Writer %d is writing into the database\n", temp);
    printf("Writer %d is leaving the database\n", temp);
    sem_post(&databaseAccess);

}

int main(int argc, char *argv[]) {

    int i = 0, NumberOfReaderThreads = 0, NumberofWriterThreads;
    sem_init(&readCountAccess, 0, 1);
    sem_init(&databaseAccess, 0, 1);

    pthread_t *WriterThreads, *ReaderThreads;
    printf("Enter the Number of Reader Threads\n");
    scanf("%d", &NumberOfReaderThreads);
    printf("Enter the Number of Writer Threads\n");
    scanf("%d", &NumberofWriterThreads);

    ReaderThreads = (pthread_t *) malloc(sizeof(pthread_t) * NumberOfReaderThreads);
    WriterThreads = (pthread_t *) malloc(sizeof(pthread_t) * NumberofWriterThreads);
    
    for (i = 0;i < NumberOfReaderThreads;i++) {
        pthread_create((ReaderThreads + i), NULL, Reader, (void *) i);
    }
    
    for (i = 0;i < NumberofWriterThreads;i++) {
        pthread_create((WriterThreads + i), NULL, Writer, (void *) i);
    }

    for (i = 0;i < NumberofWriterThreads;i++) {
        pthread_join(*(WriterThreads + i), NULL);
    }      

    for (i = 0;i < NumberOfReaderThreads;i++) {
        pthread_join(*(ReaderThreads + i), NULL);
    }

    sem_destroy(&databaseAccess);
    sem_destroy(&readCountAccess);

    return 0;

}