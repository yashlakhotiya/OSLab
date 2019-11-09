#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
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
	char buffer[BUFSIZ];
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

	while(process_running){
		while(shared_stuff->data_available == true){
			sleep(1);
			printf("Waiting for client....\n");
		}
		printf("Enter some text: \n");
		fgets(buffer,BUFSIZ,stdin);
		strncpy(shared_stuff->message,buffer,TEXT_SZ);
		shared_stuff->data_available = true;

		if(strncmp(buffer,"end",3) == 0){
			process_running = false;
		}
	}
	if(shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}