#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
void* reader(void*);
void* writer(void*);
int getItemforBuff();
void readItemfromBuff(int buffer);
int buff;
sem_t s;
int flag=0;
int main()
{
    pthread_t rd_tid;
    pthread_t wr_tid;
    sem_init(&s,0,1);
    pthread_create(&wr_tid,NULL,writer,NULL);
    pthread_create(&rd_tid,NULL,reader,NULL);
    pthread_join(wr_tid,NULL);
    pthread_join(rd_tid,NULL);
    return 0;
}
void* reader(void *argp)
{
    while(1){
        sem_wait(&s);
        if(flag==1){
            readItemfromBuff(buff);
            flag=0;
        }
        sem_post(&s);
    }
}
void* writer(void* argp)
{
    while(1){
        sem_wait(&s);
        if(flag==0){
            buff=getItemforBuff();
            flag=1;
        }
        sem_post(&s);
    }
}
int getItemforBuff()
{
    int item;
    printf("writer:ENTER AN ITEM INTO BUFFER\n");
    scanf("%d",&item);
    return item;
}
void readItemfromBuff(int buffer)
{
    printf("reader:READ ITEM FROM BUFFER=%d\n",buffer);
}