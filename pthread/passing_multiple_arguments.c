#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

struct arg{
	int size;
	int arr[20];
};

void* print_array(void* pointer){
	struct arg *arguments = (struct arg*)pointer;
	puts("");
	for(int i = 0;i < arguments->size; i++){
		printf("%d\n",arguments->arr[i]);
	}
	pthread_exit(0);
}

int main(){
	struct arg *arguments = (struct arg *)malloc(sizeof(struct arg));
	puts("Enter array size and array");
	scanf("%d",&arguments->size);
	for(int i = 0;i < arguments->size; i++){
		scanf("%d",&arguments->arr[i]);
	}
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,print_array,(void *)arguments);
	pthread_join(tid,NULL);
}