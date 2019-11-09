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
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,p[i].burst_time,p[i].arrival_time,p[i].start_time,p[i].end_time,p[i].turn_around_time,p[i].waiting_time);
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

void rr(int n, struct process p[n], int quantum){
	int remaining_time[n];
	for(int i=0; i<n; i++){
		remaining_time[i] = p[i].burst_time;
		p[i].start_time = -1;
	}
	int t=0;
	int count=0;
	int i=0;
	printf("process\ttime\n");
	while(count != n){
		if(p[i].arrival_time <= t){
			if(remaining_time[i] != 0){
				printf("%d\t%d\n",i+1,t);
				if(p[i].start_time == -1){
					p[i].start_time = t;
				}
				if(remaining_time[i] >= quantum){
					remaining_time[i] -= quantum;
					t += quantum;
				}
				else{
					t += remaining_time[i];
					remaining_time[i] = 0;
				}
				if(remaining_time[i] == 0){
					p[i].end_time = t;
					count++;
				}
			}
			i = (i+1)%n;
		}
		else{
			i = 0;
		}
	}
	for(int i=0; i<n; i++){
		p[i].turn_around_time = p[i].end_time - p[i].arrival_time;
		p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
	}
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
	int quantum = 2;
	rr(n,p,quantum);
}