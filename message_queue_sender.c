#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

struct message{
	long int type;
	char message[1024];
};

int main(){

	struct message msg;
	int running = 1;
	char buffer[1024];
	int mid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(mid == -1){
		printf("Error creating mid\n");
		exit(EXIT_FAILURE);
	}
	while(running){
		printf("Enter message to send\n");
		fgets(buffer,BUFSIZ,stdin);

		msg.type = 1;
		strcpy(msg.message,buffer);

		if(msgsnd(mid,(void *)&msg,1024,0) == -1){
			perror("error\n");
			exit(EXIT_FAILURE);
		}
		if(strncmp(buffer,"end",3) == 0){
			running = 0;
		}
	}
	exit(EXIT_SUCCESS);
}