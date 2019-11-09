#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<limits.h>
#include<errno.h>
#include<sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024 * 1024 * 10)

int main(){
	char buffer[BUFFER_SIZE+1];
	if(access(FIFO_NAME,F_OK) == -1){
		int res = mkfifo(FIFO_NAME,0777);
		if(res != 0){
			printf("could not create fifo %s \n",FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}

	int pipe_fd = open(FIFO_NAME,O_WRONLY);
	if(pipe_fd != -1){
		while(strncmp(buffer,"end",3) != 0){
			fgets(buffer,BUFFER_SIZE,stdin);
			int res = write(pipe_fd,buffer,BUFFER_SIZE);
			if(res == -1){
				perror("write error on pipe\n");
				exit(EXIT_FAILURE);
			}
		}
		close(pipe_fd);
	}
	else{
		exit(EXIT_FAILURE);
	}
}