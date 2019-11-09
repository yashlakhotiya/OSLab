#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
	if(fork() == 0){
		int n = getppid();
		//printf("Child\n");
		printf("Child %d\n",n);
		sleep(5);
		n = getppid();
		printf("Child %d\n",n);
	}
	else{
		printf("Parent\n");
		int m = getpid();
		printf("Parent %d\n",m);
	}
}