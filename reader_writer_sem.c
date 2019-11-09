#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h> //sleep()

sem_t wrt,mutex;
int read_count = 0, data = 0;

void* writer(void *param){
	do{
		sem_wait(&wrt);
		int i = *(int *)param;
		printf("writer %d writing\n",i+1);
		data++;
		sleep(1);
		printf("done\n");
		sem_post(&wrt);
		sleep(4);
	}
	while(1);
}

void* reader(void *param){
	do{
		sem_wait(&mutex);
		read_count++;
		if(read_count == 1){
			sem_wait(&wrt);
		}
		sem_post(&mutex);

		int i = *(int *)param;
		int read = data;
		printf("reader %d reading: %d\n",i+1,read);
		sleep(2);
		sem_wait(&mutex);
		read_count--;
		if(read_count == 0){
			sem_post(&wrt);
		}
		printf("done\n");
		sem_post(&mutex);
		sleep(3);
	}
	while(1);
}

int main(){
	sem_init(&wrt,0,1);
	sem_init(&mutex,0,1);

	pthread_t reader_th[4];
	pthread_t writer_th[4];

	int i=0,j=1,k=2,l=3;

	pthread_create(&reader_th[i],0,&reader,&i);
	pthread_create(&writer_th[j],0,&writer,&j);
	pthread_create(&reader_th[k],0,&reader,&k);
	pthread_create(&writer_th[l],0,&writer,&l);
	
	for(int m=0; m<4; m++){
		pthread_join(reader_th[m],0);
		pthread_join(writer_th[m],0);
	}
	sem_destroy(&wrt);
	sem_destroy(&mutex);
	return 0;
}