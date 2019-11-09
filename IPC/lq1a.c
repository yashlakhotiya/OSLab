#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<unistd.h>
#include<fcntl.h>

struct msg{
	long int message_type;
	int number;
};

int main(){
	int msgid = msgget((key_t)1234,0666|IPC_CREAT);
	assert(msgid != -1);
	int num;
	puts("Enter number to send");
	scanf("%d",&num);
	struct msg message;
	message.message_type = 1;
	message.number = num;
	msgsnd(msgid,(void *)&message,sizeof(message),0);
	msgctl(msgid,IPC_RMID,0);
}
