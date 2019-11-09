#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
	pid_t pid;
	char buf;
	int fd[2];
	assert(argc == 2); //Will give aborted, core dumped with no arguments i.e. abort the program
	int n = pipe(fd);
	if(n == -1){
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
	pid = fork();

	if(pid == -1){
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0){
		close(fd[1]);
		while(read(fd[0],&buf,1) > 0){
			write(STDOUT_FILENO,&buf,1);
		}
		write(STDOUT_FILENO,"\n",1);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	else{
		close(fd[0]);
		write(fd[1],argv[1],strlen(argv[1]));
		close(fd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
}