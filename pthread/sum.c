#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int sum = 0;

void* find_sum_thread(void* arg){
	int *temp = (int *)arg;
	int n = *temp;

	for(int i = 0;i < n; i++){
		sum+=i;
	}
	pthread_exit(0);
}

int main(int argc,char **argv){
	if(argc < 2){
		puts("Enter arguments");
		exit(-1);
	}

	int limit = atoi(argv[1]);
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,find_sum_thread,&limit);
	//void **exit_code;
	pthread_join(tid,NULL);
	printf("Sum is %d\n",sum);
	//printf("Exit code is %d\n",(*(*(int**)exit_code)));
}