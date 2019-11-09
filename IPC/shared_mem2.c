#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>

#define TEXT_SZ 2048
#define true 1
#define false 0

struct shared_use_st{
	int data_available;
	char message[TEXT_SZ];
};

int main(){
	int process_running = true;
	void *shared_memory = (void *)0;

	struct shared_use_st *shared_stuff;
	int shmid;

	shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
	if(shmid == -1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid,(void *)0,0);

	if(shared_memory == (void *)-1){
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("memory attached at %x\n",(int) shared_memory);
	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->data_available = false;
	while(process_running){
		while(shared_stuff->data_available == true){
			printf("You wrote: %s\n",shared_stuff->message);
			sleep(rand()%4);
			shared_stuff->data_available = false;

			if(strncmp(shared_stuff->message,"end",3) == false){
				process_running = false;
			}
		}
	}
	if(shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid,IPC_RMID,0) == -1){
		fprintf(stderr, "failed to delete\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}