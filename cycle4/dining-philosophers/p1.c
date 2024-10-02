#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MaxItems 5
#define BufferSize 5

sem_t chopstick[5];
void *philos(void *);
void eat(int);

int main() {
    
	int i, n[5];
	pthread_t T[5];
	for( i = 0; i < 5; i++)
	{
		sem_init(&chopstick[i],0,1);
	}
	for( i = 0; i < 5; i++)
	{
		n[i] = i;
		pthread_create(&T[i],NULL,philos,(void *)&n[i]);
	}
	for( i = 0; i < 5; i++)
	{
		pthread_join(T[i], NULL);
	}
    return 0;
}

void *philos(void *n)
{
	int ph = *(int *)n;
	printf("Philospher %d wants to eat\n", ph);
	printf("Philospher %d tries to pick left chopstick\n", ph);
	sem_wait(&chopstick[ph]);
	printf("Philospher %d picks left chopstick\n", ph);
	printf("Philospher %d tries to pick right chopstick\n", ph);
	sem_wait(&chopstick[(ph+1)%5]);
	printf("Philospher %d picks right chopstick\n", ph);
	eat(ph);
	sleep(2);
	printf("Philospher %d has finished eating\n", ph);
	sem_post(&chopstick[(ph+1)%5]);
	printf("Philospher %d leaves the right chopstick\n", ph);
	sem_post(&chopstick[ph]);
	printf("Philospher %d leaves the left chopstick\n", ph);	
}

void eat(int ph)
{
	printf("Philospher %d begins to eat\n", ph);
}


