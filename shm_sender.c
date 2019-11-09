#include "shm_com.h"

int main(){
	int running = 1;
	struct shared_use_st *shared_stuff;

	void *shared_memory = (void *)NULL;

	char buffer[BUFSIZ];

	int shm_id = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);
	if(shmid == -1){
		perror("error creating shared memory\n");
		exit(EXIT_FAILURE);
	}

	shared_memory = shmat(shmid,(void *)0, 0);
	if(shared_memory == (void *)-1){
		perror("shmat failed\n");
		exit(EXIT_FAILURE);
	}

	shared_stuff = (struct sared_use_st *)shared_memory;

	while(running){
		while(shared_stuff->written_by_you == 1){
			sleep(1);
			printf("Waiting for consumer to consume\n");
		}
		printf("Enter some text\n");
		fgets(buffer,BUFSIZ,stdin);
		strmcpy(shared_stuff->some_text, buffer, TEXT_SZ);
		shared_stuff->written_by_you = 1;
		if(strncmp(buffer,"end",3) == 0){
			running = 0;
		}
	}
	if(shmdt(shared_memory) == -1){
		perror("error detaching\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}