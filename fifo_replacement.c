#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void printMemory(int no_of_frames, int memory[no_of_frames]){
	for(int i=0; i<no_of_frames; i++){
		printf("%d\t",memory[i]);
	}
	puts("");
}

bool isPresent(int pageno, int no_of_frames, int memory[no_of_frames]){
	for(int i=0; i<no_of_frames; i++){
		if(memory[i] == pageno){
			return true;
		}
	}
	return false;
}

int findFIFOIndex(int no_of_frames, int memory[no_of_frames], int ref_len, int reference_string[ref_len], int ref, int k){
	int mem_index = 0;
	int min_index = 99999;

	for(int i=0; i<k; i++){
		if(reference_string[i] == ref){
			reference_string[i] = -1;
		}
	}
	for(int i=0; i<no_of_frames; i++){
		int p = memory[i];
		for(int j=0; j<ref_len; j++){
			if(reference_string[j] == p && j < min_index){
				min_index = j;
				mem_index = i;
				break;
			}
		}
	}
	reference_string[min_index] = -1;
	return mem_index;
}

void fifo(int no_of_frames, int memory[no_of_frames], int ref_len, int reference_string[ref_len]){
	int PAGE_HIT=0, PAGE_MISS=0;

	int j=0, k=0;
	while(j < no_of_frames && k < ref_len){
		if(!isPresent(reference_string[k],no_of_frames,memory)){
			PAGE_MISS++;
			memory[j] = reference_string[k];
			j++;
		}
		else{
			PAGE_HIT++;
		}
		printf("incoming page %d\t|\t",reference_string[k]);
		printMemory(no_of_frames,memory);
		k++;
	}

	for( ; k<ref_len; k++){
		if(!isPresent(reference_string[k],no_of_frames,memory)){
			PAGE_MISS++;
			int index = findFIFOIndex(no_of_frames,memory,ref_len,reference_string,reference_string[k],k);
			memory[index] = reference_string[k];
		}
		else{
			
			PAGE_HIT++;
		}
		printf("incoming page %d\t|\t",reference_string[k]);
		printMemory(no_of_frames,memory);
	}

}

int main(){
	printf("Enter no of frames in main memory\n");

	int no_of_frames;
	scanf("%d",&no_of_frames);
	int memory[no_of_frames];

	for(int i=0; i<no_of_frames; i++){
		memory[i] = -1;
	}

	printf("Enter reference string size\n");
	int ref_len;
	scanf("%d",&ref_len);
	int reference_string[ref_len];
	printf("Enter reference_string\n");
	for(int i=0; i<ref_len; i++){
		scanf("%d",&reference_string[i]);
	}

	fifo(no_of_frames,memory,ref_len,reference_string);
}