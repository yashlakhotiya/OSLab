#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define size 100000

sem_t mutex,full,empty;
int buffer[size],f,r;

void* producer(void *param){
	for(int i=0; i<1000; i++){
		int item = i;//item is produced
		sem_wait(&empty);
		sem_wait(&mutex);

		printf("produced item is %d \n",i);
		buffer[(r++)%size] = i;
		 r = r%size;
		//sleep(1);

		sem_post(&mutex);
		sem_post(&full);
	}
}

void* consumer(void *param){
	for(int i=0; i< 1000; i++){
		sem_wait(&full);
		sem_wait(&mutex);

		int item = buffer[(f++)%size];
		f = f%size;
		printf("item consumed is %d\n",item);
		//sleep(1);

		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main(){
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,size);
	f = r = 0;

	pthread_t prod,cons;
	pthread_create(&prod,0,&producer,0);
	pthread_create(&cons,0,&consumer,0);
	pthread_join(prod,0);
	pthread_join(cons,0);
	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}