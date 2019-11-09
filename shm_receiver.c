#include "shm_com.h"

int main(){
	int running = 1;

	char buffer[BUFSIZ];

	struct shared_use_st *shared_stuff;

	void *shared_memory = (void *)NULL;

	int shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
	if(shmid == -1){
		perror("error creating shmid\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)-1){
		perror("Error attaching memory\n");
		exit(EXIT_FAILURE);
	}

	shared_stuff = (struct shared_use_st*)shared_memory;

	while(running){
		while(shared_stuff->written_by_you == 0){
			sleep(1);
			printf("waiting for sender to send\n");
		}
		strcpy(buffer,shared_stuff->some_text);
		printf("message received is %s\n",buffer);
		sleep(3);
		shared_stuff->written_by_you = 0;
		if(strncmp(buffer,"end",3) == 0){
			running = 0;
		}
	}

	if(shmdt(shared_memory) == -1){
		perror("shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid,IPC_RMID,0) == -1){
		perror("shmctl IPC_RMID failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}