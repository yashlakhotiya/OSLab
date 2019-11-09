#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
	int n;
	int fd[2];
	char buf[1025];
	char *data = "Hello World!";
	pipe(fd);
	write(fd[1],data,strlen(data)); //writes the required number of bytes given in function and the data into the file pipe pointed by file descriptor fd[1]
	if((n = read(fd[0],buf,1024)) >= 0){//reads from the read end of the pipe
		buf[n] = '\0';
		printf("read %d bytes from the pipe: %s\n",n,buf);
	}
	else{
		perror("read");
	}
	exit(0);
}