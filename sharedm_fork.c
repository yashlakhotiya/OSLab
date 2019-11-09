#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/stat.h>

struct message{
	int is_written;
	char alphabet;
};

int main(){
	int shmid = shmget((key_t)1234, sizeof(struct message), 0666|IPC_CREAT);
	if(shmid == -1){
		printf("error creating shmid\n");
		exit(EXIT_FAILURE);
	}

	void *shared_memory = (void *)NULL;
	shared_memory = shmat(shmid,(void *)0,0);

	struct message *shared_stuff;
	shared_stuff = (struct message*)shared_memory;
	shared_stuff->is_written = 0;

	int res = fork();

	if(res == -1){
		printf("fork failed\n");
		exit(EXIT_FAILURE);
	}
	else if(res == 0){
		//child
		int running = 1;
		while(running){
			while(shared_stuff->is_written == 0 || shared_stuff->is_written == 2){
				printf("waiting for parent to write and read back again\n");
				sleep(1);
			}
			if(shared_stuff->is_written == 1){
				char c = shared_stuff->alphabet;
				if(c == 'e') running = 0;
				else{
					shared_stuff->alphabet += 1;
					shared_stuff->is_written = 2;
				}
			}
		}
	}
	else{
		//parent
		int running = 1;
		while(running){
			while(shared_stuff->is_written  == 1){
				printf("waiting for child to read and write back again\n");
				sleep(1);
			}
			if(shared_stuff->is_written == 2){
				char c = shared_stuff->alphabet;
				printf("alphabet sent back from child is %c \n",c);
				shared_stuff->is_written = 0;
			}
			if(shared_stuff->is_written == 0){
				puts("enter alphabet");
				char c;
				scanf("%c",&c);
				shared_stuff->alphabet = c;
				shared_stuff->is_written = 1;
				if(c == 'e') running = 0;
			}
		}
	}
	shmdt(shared_memory);
	shmctl(shmid,IPC_RMID,0);

}