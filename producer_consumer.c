#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
sem_t e,f,s;

int data[5],in=0,out=0;
void * producer(void * arg)
{
    sem_wait(&e);
    sem_wait(&s);
    data[in]=rand();
    printf("\nProducer generated : %d",data[in]);
    in=(in+1)%5;
    sem_post(&s);
    sem_post(&f);
}
void * consumer(void * arg){
    int value;
    do{
        sem_wait(&f);
        sem_wait(&s);
        value=data[out];
        printf("\nConsumer read: %d",value);
        out=(out+1)%5;
        sem_post(&s);
        sem_post(&e);
        sem_getvalue(&e,&value);
    }
    while(value!=5);
}
void main(){
    pthread_t p[8],c[8];
    int i;

    sem_init(&f,0,0);
    sem_init(&e,0,5);
    sem_init(&s,0,1);

    for(i=0;i<8;++i)
    pthread_create(&c[i],NULL,consumer,NULL);

    sleep(2);
    for(i=0;i<8;++i)
    pthread_create(&p[i],NULL,producer,NULL);

    sleep(2);
}



