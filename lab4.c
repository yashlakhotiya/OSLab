#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<dirent.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

int main(){
	DIR *d;
	struct dirent *p;
	puts("Enter directory");
	char dir[20];
	gets(dir);
	d = opendir(dir);
	int fh1 = creat("text_doc.txt",S_IRWXU);
	fh1 = open("text_doc.txt",O_RDWR);
	while(p = readdir(d)){
		char file_name[20];
		if(file_name)
		strcpy(file_name,p->d_name);
		int fh = open(file_name,O_RDONLY);
		char buf[1024];
		int n = read(fh,buf,sizeof(buf));
		write(fh1,"\n",1);
		write(fh1,file_name,strlen(file_name));
		write(fh1,"\n",1);
		buf[n] = '\0';
		write(fh1,buf,strlen(buf));
		close(fh);
	}
	int offset = lseek(fh1,10,SEEK_SET); //from starting position
	printf("offset %d\n",offset);
	char buf[1024];
	strcpy(buf,"DOCUMENT STARTED");
	write(fh1,buf,strlen(buf));
	close(fh1);
}