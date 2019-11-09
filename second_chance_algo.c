#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void printMemory(int cur_index, int no_of_frames, int memory[no_of_frames], int second_chance[no_of_frames]){
	for(int i=0; i<no_of_frames; i++){
		if(i == cur_index) printf("*");
		printf("%d\t",memory[i]);
	}
	printf("\t\t");
	for(int i=0; i<no_of_frames; i++){
		if(i == cur_index) printf("*");
		printf("%d\t",second_chance[i]);
	}
	puts("");
}

void inputReferenceString(int ref_string_size, int reference_string[ref_string_size]){
	for(int i=0; i<ref_string_size; i++){
		scanf("%d",&reference_string[i]);
	}
}

int searchPageInMemory(int no_of_frames, int memory[no_of_frames], int ele){
	int index=-1;
	for(int i=0; i<no_of_frames; i++){
		if(memory[i] == ele){
			index = i;
			break;
		}
	}
	return index;
}

int findPageToReplace(int no_of_frames, int second_chance[no_of_frames],int *cur_index){
	int i = *cur_index;
	while(second_chance[i] == 1){
		second_chance[i] = 0;
		i = (i+1)%no_of_frames;
	}
	*cur_index = (i+1)%no_of_frames;
	return i;
}

void secondChance(int no_of_frames, int memory[no_of_frames], int ref_string_size, int reference_string[ref_string_size]){
	int PAGE_HIT=0, PAGE_MISS=0;
	int cur_index=0;
	int second_chance[no_of_frames];
	for(int i=0; i<no_of_frames; i++){
		second_chance[i] = 0;
	}

	int j=0, k=0;
	while(j < no_of_frames && k < ref_string_size){
		int m = searchPageInMemory(no_of_frames,memory,reference_string[k]);
		if(m == -1){
			PAGE_MISS++;
			memory[j] = reference_string[k];
			j++;
		}
		else{
			if(second_chance[m] != 1){
				second_chance[m] = 1;
			}
			PAGE_HIT++;
		}
		printf("incoming page %d\t|\t",reference_string[k]);
		printMemory(cur_index,no_of_frames,memory,second_chance);
		k++;
	}

	for( ; k<ref_string_size; k++){
		int m = searchPageInMemory(no_of_frames,memory,reference_string[k]);
		if(m == -1){
			PAGE_MISS++;
			int index = findPageToReplace(no_of_frames,second_chance,&cur_index);
			memory[index] = reference_string[k];
		}
		else{
			if(second_chance[m] != 1){
				second_chance[m] = 1;
			}
			PAGE_HIT++;
		}
		printf("incoming page %d\t|\t",reference_string[k]);
		printMemory(cur_index,no_of_frames,memory,second_chance);
	}
}

int main(){
	printf("Enter number of frames in main memory\n");
	int no_of_frames;
	scanf("%d",&no_of_frames);
	int memory[no_of_frames];
	memset(memory,-1,no_of_frames*sizeof(memory[0]));

	int ref_string_size;
	puts("Enter size of memory reference string");
	scanf("%d",&ref_string_size);
	puts("Enter reference string");
	int reference_string[ref_string_size];
	inputReferenceString(ref_string_size,reference_string);
	secondChance(no_of_frames,memory,ref_string_size,reference_string);
}