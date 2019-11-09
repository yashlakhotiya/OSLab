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

void print_gantt_chart(int n, struct process p[n]){
	puts("********************************************");
	for(int i=0; i<n; i++){
		printf("P%d\t",i);
	}
	puts("");
	for(int i=0; i<n; i++){
		printf("%d\t",p[i].start_time);
	}
	puts("");
	puts("********************************************");
}

void fcfs(int n, struct process p[n]){
	int t=0;
	int i=0;
	while(i < n){
		if(p[i].arrival_time <= t){
			p[i].start_time = t;
			p[i].end_time = p[i].start_time + p[i].burst_time;
			p[i].turn_around_time = p[i].end_time - p[i].arrival_time;
			p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
			t += p[i].burst_time;
			i++;
		}
		else{
			t++;
		}
	}
	print_gantt_chart(n,p);
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
	fcfs(n,p);
}