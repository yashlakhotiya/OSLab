#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int size;

void* print_array(void* pointer){
	int *temp = (int *)pointer;
	puts("");
	for(int i = 0;i < size; i++){
		printf("%d\n",temp[i]);
	}
	pthread_exit(0);
}

int main(){
	puts("Enter array size and array");
	int n;
	scanf("%d",&n);
	size = n;
	int arr[n];
	for(int i = 0;i < n; i++){
		scanf("%d",&arr[i]);
	}


	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,print_array,arr);
	pthread_join(tid,NULL);
}