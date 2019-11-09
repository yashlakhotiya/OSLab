#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

int ind = 0;
int ll,ul,prime[20];

int check_prime(int n){
	int flag = 1;
	for(int i = 2; i <= sqrt(n); i++){
		if(n%i == 0){
			flag = 0;
			break;
		}
	}
	return flag;
}

void* prime_runner(void *param){
	if(ll = 1) ll+=1;
	for(int i = ll; i <= ul; i++){
		if(check_prime(i)){
			prime[ind++] = i;
		}
	}
	pthread_exit(0);
}

int main(int argc, char **argv){
	if(argc < 3){
		puts("Give arguments properly");
		exit(0);
	}
	ll = atoi(argv[1]);
	ul = atoi(argv[2]);

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,prime_runner,NULL);
	pthread_join(tid,NULL);

	for(int i = 0;i < ind; i++){
		printf("%d\t",prime[i]);
	}

}