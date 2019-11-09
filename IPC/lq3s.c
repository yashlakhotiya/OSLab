#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<fcntl.h>
#include<sys/shm.h>
#define true 1
#define false 0

struct message{
	int data_available;
	char message;
};

int main(){
	int process_running = 1;

	int shmid = shmget((key_t)1234,sizeof(struct message),0666|IPC_CREAT);

	void *memory = shmat(shmid,(void *)0,0);

	struct message *shared_stuff = (struct message*)memory;
	shared_stuff->data_available = false;
	char c;
	while(process_running){
		while(shared_stuff->data_available == true){
			puts("Waiting for client");
		}
		printf("Enter character\n");
		c = getc(stdin);
		fflush(stdin);
		shared_stuff->message = c;
		shared_stuff->data_available = true;
		if(c == '#'){
			process_running = 0;
		}
	}
	shmdt(memory);
}