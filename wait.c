#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
	int status;
	pid_t pid;
	pid = fork();
	if(pid == -1){
		puts("Fork failed");
		exit(-1);
	}
	else if(pid == 0){
		puts("I am the child");
		exit(0);
	}
	else{
		wait(&status);
		printf("I am the parent\n");
		printf("Child returned %d",status);
	}
}