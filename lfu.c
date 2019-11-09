#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void inputReferenceString(int ref_string_size, int reference_string[ref_string_size]){
	for(int i=0; i<ref_string_size; i++){
		scanf("%d",&reference_string[i]);
	}
}

void printMemory(int no_of_frames, int memory[no_of_frames]){
	for(int i=0; i<no_of_frames; i++){
		printf("%d\t",memory[i]);
	}
	puts("");
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

int findReferenceIndex(int ele, int ref_string_size, int reference_string[ref_string_size]){
	int index = 0;
	for(int i=0; i<ref_string_size; i++){
		if(reference_string[i] != -1 && ele == reference_string[i]){
			index = i;
			break;
		}
	}
	return index;
}

int findMinimumFrequency(int ref_string_size,int frequency[ref_string_size], int no_of_frames, int memory[no_of_frames]){
	int min = frequency[memory[0]];
	int index = 0;
	for(int i=0; i<no_of_frames; i++){
		if(frequency[memory[i]] < min){
			min = frequency[i];
			index = i;
		}
	}
	return min;
}

int findVictimIndex(int k, int no_of_frames, int memory[no_of_frames], int ref_string_size, int reference_string[ref_string_size], int frequency[ref_string_size]){
	int min = findMinimumFrequency(ref_string_size,frequency,no_of_frames,memory);
	int index = -1;
	for(int i=0; i<k; i++){
		if(frequency[reference_string[i]] == min && reference_string[i] != -1){
			int m = searchPageInMemory(no_of_frames,memory,reference_string[i]);
			if(m != -1){
				return m;
			}
		}
	}
}

void lfu(int no_of_frames, int memory[no_of_frames], int ref_string_size, int reference_string[ref_string_size]){
	int j=0,k=0;
	int PAGE_HIT=0, PAGE_MISS=0;
	int frequency[20]; //pages can be in between 0 and 19
	for(int i=0; i<20; i++) frequency[i] = 0;
	
	while(j < no_of_frames && k < ref_string_size){
		int m = searchPageInMemory(no_of_frames,memory,reference_string[k]);
		if(m == -1){
			PAGE_MISS++;
			memory[j] = reference_string[k];
			frequency[reference_string[k]]++;
			j++;
		}
		else{
			frequency[reference_string[k]]++;
			PAGE_HIT++;
		}
		k++;
		printMemory(no_of_frames,memory);
	}

	for( ; k < ref_string_size; k++){
		int m = searchPageInMemory(no_of_frames,memory,reference_string[k]);
		if(m == -1){
			PAGE_MISS++;
			int index = findVictimIndex(k,no_of_frames,memory,ref_string_size,reference_string,frequency);
			int ref_i = findReferenceIndex(memory[index],ref_string_size,reference_string);
			reference_string[ref_i] = -1;
			frequency[memory[index]] = 0;
			memory[index] = reference_string[k];
			frequency[reference_string[k]]++;
		}
		else{
			frequency[reference_string[k]]++;
			PAGE_HIT++;
		}
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
	lfu(no_of_frames,memory,ref_string_size,reference_string);
}