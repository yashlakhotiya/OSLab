#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* increment(void *n){
	int *m;
	m = (int *)malloc(sizeof(int));
	*m = *((int *)n);
	*m += 1;
	return (void *)m;
}

int main(){
	pthread_t tid;
	int n = 1;
	pthread_create(&tid,0,&increment,(void *)&n);
	int *result;
	pthread_join(tid,(void *)&result);
	printf("%d\n",*result);
}