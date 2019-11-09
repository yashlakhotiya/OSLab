#include<stdio.h>
#include<stdlib.h>

void scan(int n, int disc[n], int head, int no_of_req){
	int thm = 0;
	int count = 0;
	for(int i=head+1; i<n; i++){
		if(disc[i] == 1){
			printf("servicing %d\n",i);
			disc[i] = 0;
			count++;
		}
		thm++;
	}
	for (int i = n-2; i >= 0; i--)
	{
		if(count == no_of_req){
			break;
		}
		if(disc[i] == 1){
			printf("servicing %d\n",i);
			disc[i] = 0;
			count++;
		}
		thm++;
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