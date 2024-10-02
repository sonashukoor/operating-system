#include <pthread.h>
#include <semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 5
#define BUFFER 5
int buffer[BUFFER];
int in = 0, out = 0;
pthread_mutex_t mutex;
sem_t full, empty;

void *producer(void *pno)
{
    int item;
    for(int i = 0; i < MAX; i++)
    {
        item =  rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: insert item %d in buffer at %d\n", *((int *)pno), buffer[in], in);
        in =(in+1)%BUFFER;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *cno)
{
    for(int i = 0; i < MAX; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove item %d in buffer at %d\n", *((int *)cno), buffer[out], out);
        out = (out+1)%BUFFER;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}
int main()
{
    sem_init(&empty, 0 , BUFFER);
    sem_init(&full, 0 ,0);
    pthread_mutex_init(&mutex, NULL);
    int a[5] ={1,2,3,4,5};
    pthread_t pno[5], cno[5];

    for(int i = 0; i < 5; i++)
    {
        pthread_create(&pno[i], NULL, (void *)producer, (void *)&a[i]);
    }
        for(int i = 0; i < 5; i++)
    {
        pthread_create(&cno[i], NULL, (void *)consumer, (void *)&a[i]);
        
    }
        for(int i = 0; i < 5; i++)
    {
        pthread_join(pno[i], NULL);
    }
        for(int i = 0; i < 5; i++)
    {
        pthread_join(cno[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
     sem_destroy(&empty);

}
