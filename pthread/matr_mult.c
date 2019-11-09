#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define row1 3
#define row2 3
#define col1 3
#define col2 3

struct pair{
	int i,k;
};

int a[row1][col1],b[row2][col2],c[row1][col2];

void printMatrix(){
	printf("\n");
	for(int i=0; i<row1; i++){
		for(int j=0; j<col2; j++){
			printf("%d\t",c[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void* multiply(void *arg){
	struct pair *p = (struct pair*)arg;
	int i = p->i;
	int k = p->k;
	printf("calculating c[%d][%d]\n",i,k);
	for(int j=0; j<col1; j++){
		c[i][k] = c[i][k] + a[i][j] * b[j][k];
	}
	printMatrix();
}

int main(){
	puts("Enter matrix 1");
	for(int i=0; i<row1; i++){
		for(int j=0; j<col1; j++){
			scanf("%d",&a[i][j]);
		}
	}
	puts("Enter matrix 2");
	for(int i=0; i<row2; i++){
		for(int j=0; j<col2; j++){
			scanf("%d",&b[i][j]);
		}
	}
	pthread_t tid[col2];
	for(int i=0; i<row1; i++){
		for(int k=0; k<col2; k++){
			struct pair *p = (struct pair*)malloc(sizeof(struct pair));
			p->i = i;
			p->k = k;
			pthread_create(&tid[k],0,&multiply,(void *)p);
			pthread_join(tid[k],NULL);
		}
	}
	printMatrix();
}

/*int row1,col1,row2,col2;
	puts("Enter row1 and col1 no");
	scanf("%d%d",&row1,&col1);
	int mat1[row1][col1];
	puts("Enter matrix");
	for(int i=0; i<row1; i++){
		for(int j=0; j<col1; j++){
			scanf("%d",&mat1[i][j]);
		}
	}
	puts("Enter row2 and col2 no");
	scanf("%d%d",&row2,&col2);
	if(col1 != row2){
		perror("col1 != row2");
		exit(-1);
	}
	int mat2[row2][col2];
	puts("Enter matrix");
	for(int i=0; i<row2; i++){
		for(int j=0; j<col2; j++){
			scanf("%d",&mat2[i][j]);
		}
	}*/