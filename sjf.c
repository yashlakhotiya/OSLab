#include<stdio.h>
#include<stdlib.h>

struct process{
	int arrival_time;
	int start_time;
	int burst_time;
	int end_time;
	int priority;
	int turn_around_time;
	int waiting_time;
};

void print_process_chart(int n, struct process p[n]){
	puts("********************************************");
	printf("pid\tburst\tarrival\tstart\tend\ttat\twt\n");
	for(int i=0; i<n; i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,p[i].burst_time,p[i].arrival_time,p[i].start_time,p[i].end_time,p[i].turn_around_time,p[i].waiting_time);
	}
	puts("********************************************");
}

void print_gantt_chart(int n, struct process p[n], int sequence[n]){
	puts("********************************************");
	for(int i=0; i<n; i++){
		int index = sequence[i];
		printf("P%d\t",index);
	}
	puts("");
	for(int i=0; i<n; i++){
		int index = sequence[i];
		printf("%d\t",p[index].start_time);
	}
	puts("");
	puts("********************************************");
}

int findShortestJob(int n, struct process p[n], int flag[n], int t){
	int index = -1;
	int min = 999999;
	for(int i=0; i<n; i++){
		if(flag[i] == 0 && p[i].arrival_time <= t){
			if(p[i].burst_time < min){
				min = p[i].burst_time;
				index = i;
			}
		}
	}
	return index;
}

void sjf(int n, struct process p[n], int flag[n],int sequence[n]){
	int t=0;
	int i=0;
	while(i<n){
		int index = findShortestJob(n,p,flag,t);
		if(index == -1){
			t++;
			continue;
		}
		sequence[i] = index;
		p[index].start_time = t;
		p[index].end_time = p[index].start_time + p[index].burst_time;
		p[index].turn_around_time = p[index].end_time - p[index].arrival_time;
		p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
		t += p[index].burst_time;
		flag[index] = 1;
		i++;
	}
	print_gantt_chart(n,p,sequence);
	print_process_chart(n,p);
}

int main(){
	int n;
	puts("Enter the no of process");
	scanf("%d",&n);
	struct process p[n];
	printf("Enter processes: arrival_time and burst_time\n");
	for(int i=0; i<n; i++){
		scanf("%d%d",&p[i].arrival_time,&p[i].burst_time);
	}
	int *flag,*sequence;
	flag = (int *)calloc(n,sizeof(int));
	sequence = (int *)calloc(n,sizeof(int));
	sjf(n,p,flag,sequence);
}