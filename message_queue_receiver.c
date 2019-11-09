#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#define MAX_TEXT 512

struct message{
	long int type;
	char message[BUFSIZ];
};

int main(){
	struct message msg;
	int running = 1;
	long int message_to_receive = 0;
	int mid = msgget((key_t)1234, 0666|IPC_CREAT);
	if(mid == -1){
		printf("msgget failed\n");
		exit(EXIT_FAILURE);
	}

	while(running){
		if(msgrcv(mid,(void *)&msg,BUFSIZ,message_to_receive,0) == -1){
			perror("error receiving\n");
			exit(EXIT_FAILURE);
		}
		printf("message is : %s\n",msg.message);
		if(strncmp(msg.message,"end",3) == 0){
			running = 0;
		}
	}
	if(msgctl(mid,IPC_RMID,0) == -1){
		perror("error to remove\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}