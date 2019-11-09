#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t semaphore;

void *func1(void *param){
	printf("thread1\n");
	sem_post(&semaphore);
}

void *func2(void *param){
	sem_wait(&semaphore);
	printf("thread2\n");
}

int main(){
	pthread_t t1,t2;
	sem_init(&semaphore,0,0);
	pthread_create(&t1,0,&func1,0);
	pthread_create(&t2,0,&func2,0);
	pthread_join(t1,0);
	pthread_join(t2,0);
	sem_destroy(&semaphore);
	return 0;
}