#include<stdio.h>
#include<stdlib.h>

void scan(int n, int disc[n], int head, int no_of_req){
	int thm = 0;
	int count = 0;
	int i = head+1;
	while(count != no_of_req && i < n){
		if(disc[i] == 1){
			printf("servicing %d\n",i);
			disc[i] = 0;
			count++;
		}
		i = (i+1)%n;
		if(i == 0){
			thm += n-1;
		}
		else thm++;
	}
	printf("thm is %d \n",thm);
}

int main(){
	puts("enter no of cyender");
	int n;
	scanf("%d",&n);
	int disc[n];
	for (int i = 0; i < n; ++i)
	{
 		disc[i] = -1;
	}
	puts("enter position of head");
	int head;
	scanf("%d",&head);
	puts("enter no of req");
	int req;
	scanf("%d",&req);
	puts("enter requests");
	int val;
	for (int i = 0; i < req; ++i)
	{
 		scanf("%d",&val);
 		disc[val] = 1;
	}
	scan(n,disc,head,req);
}