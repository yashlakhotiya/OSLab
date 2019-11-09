#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct proc{
	int size;
	bool allocated;
}PROCESS;

typedef struct par{
	int total_size;
	int vacant_size;
	int number_of_process;
	bool is_full;
}PARTITION;

void printMatrix(int m, PARTITION par[m]){
	puts("*************************************************************************************");
	printf("p_no\ttot_size\tsize_left\tno_of_pro\n");
	for(int i=0; i<m; i++){
		printf("%d\t   %d\t\t  %d\t\t  %d\n",i+1,par[i].total_size,par[i].vacant_size,par[i].number_of_process);
	}
	puts("*************************************************************************************");
}

int findFirstIndex(PROCESS pro, int m, PARTITION par[m]){
	int index = -1;
	for(int i=0; i<m; i++){
		if(!par[i].is_full && !pro.allocated){
			if(pro.size <= par[i].vacant_size){
				index = i;
				break;
			}
		}
	}
	return index;
}

void firstFit(int m, PARTITION par[m], int n, PROCESS pro[n]){
	for(int i=0; i<n; i++){
		int count = 0;
		int index = findFirstIndex(pro[i],m,par);
		if(index != -1){
			printf("process %d allocated to partition %d\n",i+1,index+1);
			par[index].vacant_size -= pro[i].size;
			if(par[index].vacant_size == 0){
				par[index].is_full = true;
			}
			par[index].number_of_process++;
			pro[i].allocated = true;
		}
		else{
			printf("No partition found for process %d\n",i+1);
		}
	}
	printMatrix(m,par);
}

int findBestIndex(PROCESS pro, int m, PARTITION par[m]){
	int index = -1;
	int min = 99999999;
	for(int i=0; i<m; i++){
		if(!par[i].is_full && !pro.allocated){
			if(pro.size <= par[i].vacant_size && par[i].vacant_size < min){
				min = par[i].vacant_size;
				index = i;
			}
		}
	}
	return index;
}

void bestFit(int m, PARTITION par[m], int n, PROCESS pro[n]){
	for(int i=0; i<n; i++){
		int count = 0;
		int index = findBestIndex(pro[i],m,par);
		if(index != -1){
			printf("process %d allocated to partition %d\n",i+1,index+1);
			par[index].vacant_size -= pro[i].size;
			if(par[index].vacant_size == 0){
				par[index].is_full = true;
			}
			par[index].number_of_process++;
			pro[i].allocated = true;
		}
		else{
			printf("No partition found for process %d\n",i+1);
		}
	}
	printMatrix(m,par);
}

int findWorstIndex(PROCESS pro, int m, PARTITION par[m]){
	int index = -1;
	int max = -9999999;
	for(int i=0; i<m; i++){
		if(!par[i].is_full && !pro.allocated){
			if(pro.size <= par[i].vacant_size && par[i].vacant_size > max){
				max = par[i].vacant_size;
				index = i;
			}
		}
	}
	return index;
}

void worstFit(int m, PARTITION par[m], int n, PROCESS pro[n]){
	for(int i=0; i<n; i++){
		int count = 0;
		int index = findWorstIndex(pro[i],m,par);
		if(index != -1){
			printf("process %d allocated to partition %d\n",i+1,index+1);
			par[index].vacant_size -= pro[i].size;
			if(par[index].vacant_size == 0){
				par[index].is_full = true;
			}
			par[index].number_of_process++;
			pro[i].allocated = true;
		}
		else{
			printf("No partition found for process %d\n",i+1);
		}
	}
	printMatrix(m,par);
}


int main(){
	printf("enter number of process and partitions\n");
	int n,m;
	scanf("%d%d",&n,&m);//n: process m: partition

	PROCESS pro[n];
	PARTITION par[m];

	printf("Enter partitions\n");

	for(int i=0; i<m; i++){
		scanf("%d",&par[i].total_size);
		par[i].vacant_size = par[i].total_size;
		par[i].is_full = false;
		par[i].number_of_process = 0;
	}

	printf("Enter processes\n");

	for (int i = 0; i < n; ++i)
	{
		scanf("%d",&pro[i].size);
		pro[i].allocated = false;
	}
	firstFit(m,par,n,pro);
	//bestFit(m,par,n,pro);
	//worstFit(m,par,n,pro);
}