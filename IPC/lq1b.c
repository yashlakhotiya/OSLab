#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

struct msg{
	long int message_type;
	int number;
};

int main(){
	int msgid = msgget((key_t)1234,0666|IPC_CREAT);
	assert(msgid != -1);
	struct msg message;
	msgrcv(msgid,(void *)&message,sizeof(message),1,0);
	printf("Message received is %d\n",message.number);
	msgctl(msgid,IPC_RMID,0);
}
