#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

sem_t r,w;
int count=0;

void * Reader(void *arg)
{
    sem_wait(&r);
    count++;
    if(count==1)
    {
        sem_wait(&w);
    }
    sem_post(&r);
    printf("\nReader is reading");
    sem_wait(&r);
    count--;
    if(count==0)
    {
        sem_post(&w);
    }
    sem_post(&r);
}
void * Writer(void * arg)
{
    sem_wait(&w);
    printf("\nWriter is writing");
    sem_post(&w);
}

int main()
{
    pthread_t reader[3],writer[3];
    sem_init(&r,0,1);
    sem_init(&w,0,1);
    for(int i=0;i<3;i++)
    {
        pthread_create(&reader[i],NULL,Reader,NULL);
        pthread_create(&writer[i],NULL,Writer,NULL);
    }
    for(int i=0;i<3;i++)
    {
        pthread_join(reader[i],NULL);
        pthread_join(writer[i],NULL);
    }
    return 0;
}