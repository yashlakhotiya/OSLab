#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>

int main(){
	puts("Enter directory");
	char dir[20];
	gets(dir);
	DIR* d;
	d = opendir(dir);
	struct dirent *p;
	if(d == NULL){
		puts("Canot find directory");
		exit(-1);
	}
	while(p = readdir(d)){
		printf("%s\n",p->d_name);
	}
	return 0;
}