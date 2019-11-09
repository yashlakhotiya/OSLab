#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int es=0,os=0,n;
int *arr;

int isEven(int k){
	if(k%2 == 0) return 1;
	else return 0;
}

void* sum_runner(void *param){
	puts("Enter size and array");
	scanf("%d",&n);
	arr = (int *)malloc(n * sizeof(int));
	for(int i = 0;i < n; i++){
		scanf("%d",&arr[i]);
	}

	for(int i = 0; i < n; i++){
		if(isEven(arr[i])){
			es += arr[i];
		}
		else{
			os +=arr[i];
		}
	}
}

int main(int argc, char **argv){
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,sum_runner,NULL);
	pthread_join(tid,NULL);
	printf("Even sum is %d\n",es);
	printf("Odd sum is %d\n",os);
}