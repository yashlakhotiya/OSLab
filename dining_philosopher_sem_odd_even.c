#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdbool.h>

sem_t mutex,spoon[5];

bool isEven(int i){
	if(i%2 == 0) return true;
	return false;
}


void take_up(int param){
	int i = param;
	//sem_wait(&mutex);
	if(isEven(i)){
		sem_wait(&spoon[i]);
		printf("Philosopher %d took spoon %d\n",i,i);
		sem_wait(&spoon[(i+1)%5]);
		printf("Philosopher %d took spoon %d\n",i,(i+1)%5);
	}
	else{
		sem_wait(&spoon[(i+1)%5]);
		printf("Philosopher %d took spoon %d\n",i,(i+1)%5);
		sem_wait(&spoon[i]);
		printf("Philosopher %d took spoon %d\n",i,i);
	}
	
	//sem_post(&mutex);
}

void put_down(int param){
	int i = param;

	//sem_wait(&mutex);

	sem_post(&spoon[i]);
	printf("Philosopher %d put down spoon %d\n",i,i);
	sem_post(&spoon[(i+1)%5]);
	printf("Philosopher %d put down spoon %d\n",i,(i+1)%5);
	
	//sem_post(&mutex);
}

void* eat(void *param){
	int i = *(int *)param;
	do{
		puts("");
		printf("Philosopher %d is hungry\n",i);
		take_up(i);
		printf("Philosopher %d eating\n",i);
		sleep(2);
		put_down(i);
		printf("Philosopher %d finished eating\n",i);
		puts("");
	}
	while(1);
}

int main(){
	for(int i=0; i<5; i++){
		sem_init(&spoon[i],0,1);
	}
	sem_init(&mutex,0,1);

	pthread_t Philosopher[5];
	int a=0,b=1,c=2,d=3,e=4;
	pthread_create(&Philosopher[a],0,&eat,(void *)&a);
	pthread_create(&Philosopher[b],0,&eat,(void *)&b);
	pthread_create(&Philosopher[c],0,&eat,(void *)&c);
	pthread_create(&Philosopher[d],0,&eat,(void *)&d);
	pthread_create(&Philosopher[e],0,&eat,(void *)&e);

	for(int i=0; i<5; i++){
		pthread_join(Philosopher[i],0);
	}	
	for(int i=0; i<5; i++){
		sem_destroy(&spoon[i]);
	}
	sem_destroy(&mutex);
}
