#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
int main(){
	char buffer[BUFFER_SIZE+1];
	int pipe_fd = open(FIFO_NAME,O_RDONLY);
	if(pipe_fd != -1){
		while(strncmp(buffer,"end",3) != 0){
			read(pipe_fd,buffer,BUFFER_SIZE);
			printf("Data read is %s\n",buffer);
		}
		close(pipe_fd);
	}
	else{
		exit(EXIT_FAILURE);
	}
}