#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void printMemory(int no_of_frames, int memory[no_of_frames]){
	for(int i=0; i<no_of_frames; i++){
		printf("%d\t",memory[i]);
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

int findDistance(int ref_string_size, int reference_string[ref_string_size], int ele, int k){
	int index = -1;
	for(int i=k+1; i<ref_string_size; i++){
		if(reference_string[i] == ele){
			index = i;
			break;
		}
	}
	return index;
}

int findPageToReplace(int no_of_frames, int memory[no_of_frames], int ref_string_size, int reference_string[ref_string_size], int k){
	int max = 0;
	int index = 0;
	for(int i=0; i<no_of_frames; i++){
		int d = findDistance(ref_string_size,reference_string,memory[i],k);
		if(d == -1){
			return i;
		}
		if(d > max){
			max = d;
			index = i;
		}
	}
	return index;
}

void optimal(int no_of_frames, int memory[no_of_frames], int ref_string_size, int reference_string[ref_string_size]){
	int PAGE_HIT=0, PAGE_MISS=0;

	int j=0, k=0;
	while(j < no_of_frames && k < ref_string_size){
		if(searchPageInMemory(no_of_frames,memory,reference_string[k]) == -1){
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

	for( ; k<ref_string_size; k++){
		if(searchPageInMemory(no_of_frames,memory,reference_string[k]) == -1){
			PAGE_MISS++;
			int index = findPageToReplace(no_of_frames,memory,ref_string_size,reference_string,k);
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
	int curr_ref_index = 0;
	optimal(no_of_frames,memory,ref_string_size,reference_string);
}