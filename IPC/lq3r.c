#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<sys/shm.h>
#define true 1
#define false 0
struct message{
	int data_available;
	char message;
};

int main(){
	int shmid = shmget((key_t)1234,sizeof(struct message),0666|IPC_CREAT);
	void *memory = shmat(shmid,(void *)0,0);
	struct message *shared_stuff = (struct message *)memory;
	shared_stuff->data_available = false;
	int process_running = 1;
	char c,next;
	while(process_running){
		while(shared_stuff->data_available == true){
			c = shared_stuff->message;
			if(c != '#' && c != '\n'){
				next = c+1;
				printf("Next char is %c\n",next);
			}
				shared_stuff->data_available = false;
		}
		if(c == '#'){
			process_running = false;
		}
	}
	shmdt(memory);
}