#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
	if(fork() == 0){
		int n = getpid();
		printf("Child %d\n",n);
	}
	else{
		printf("Parent\n");
		sleep(3);
		int m = getpid();
		printf("Parent %d\n",m);
	}
	nexeclp("/bin/ps","ps",NULL);
}