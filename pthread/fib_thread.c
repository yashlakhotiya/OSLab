#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int fib[100];

void* fib_runner(void *argv){
	int *lim = (int *)argv;
	int limit = *lim;

	fib[0] = 0;
	fib[1] = 1;

	for(int i = 2;i < limit; i++){
		fib[i] = fib[i-1]+fib[i-2];
	}
	pthread_exit(0);
}

int main(int argc, char **argv){
	int limit = atoi(argv[1]);

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,fib_runner,&limit);
	pthread_join(tid,NULL);

	for(int i = 0; i < limit; i++){
		printf("%d\t",fib[i]);
	}
	puts("");
	return 0;
}