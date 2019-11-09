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
	puts("");
	puts("********************************************");
	printf("pid\tburst\tarrival\tstart\tend\ttat\twt\n");
	for(int i=0; i<n; i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,p[i].burst_time,p[i].arrival_time,p[i].start_time,p[i].end_time,p[i].turn_around_time,p[i].waiting_time);
	}
	puts("********************************************");
	puts("");
}

int findShortestJob(int n, struct process p[n], int remaining_time[n], int t){
	int min = 999999;
	int index = -1;

	for(int i=0; i<n; i++){
		if(remaining_time[i] != 0 && p[i].arrival_time <= t){
			if(remaining_time[i] < min){
				min = remaining_time[i];
				index = i;
			}
		}
	}
	return index;
}

void srtf(int n, struct process p[n]){
	int remaining_time[n];
	for(int i=0; i<n; i++){
		remaining_time[i] = p[i].burst_time;
	}

	int t = 0;
	int count = 0; //no of process executed
	while(1){
		if(count < n){
			int index = findShortestJob(n,p,remaining_time,t);
			if(index != -1){
				printf("P%d | %d\t||\t",index+1,t);
				if(p[index].start_time == -1){
					p[index].start_time = t;
				}
				remaining_time[index] -= 1;
				t++;
				if(remaining_time[index] == 0){
					count++;
					p[index].end_time = t;
					p[index].turn_around_time = p[index].end_time - p[index].arrival_time;
					p[index].waiting_time = p[index].turn_around_time - p[index].burst_time;
				}
			}
			else{
				t++;
			}
		}
		else{
			break;
		}
	}
	print_process_chart(n,p);
}

int main(){
	int n;
	printf("Enter number of processes\n");
	scanf("%d",&n);
	struct process p[n];

	printf("Enter arrival time and burst time\n");
	for(int i=0; i<n; i++){
		scanf("%d%d",&p[i].arrival_time,&p[i].burst_time);
		p[i].start_time = -1;
	}
	srtf(n,p);
}