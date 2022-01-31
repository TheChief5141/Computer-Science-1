#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student{
	char lname[50];
	int assignment;
	int finalExam;
	int total;
	int *quiz;
}students;

students* readData(FILE *in, int *noOfRecords, int *noOfQuiz){
	students *ptr;
	int i,j;
	fscanf(in, "%d %d", noOfRecords, noOfQuiz);
	ptr = (struct student*)malloc(*noOfRecords *(sizeof(struct student)));
	for(i = 0; i < *noOfRecords; ++i){
		ptr[i].quiz = (int*)malloc(*noOfQuiz * (sizeof(int)));
		fscanf(in, "%s %d", ptr[i].lname, &ptr[i].assignment);
		int quizSum = 0;
		for(j = 0; j < *noOfQuiz; ++j){
			fscanf(in, "%d", &ptr[i].quiz[j]);
			quizSum += ptr[i].quiz[j];
		}
		fscanf(in, "%d", &ptr[i].finalExam);
		ptr[i].total = ptr[i].assignment + ptr[i].finalExam + quizSum;
	}
	return ptr;
}

int main(){
	students *ptr; 
	FILE *inFile, *outFile;
	int i,j,noOfRecords, noOfQuiz;
	inFile = fopen("input.txt", "r");
	if(inFile != NULL){
		printf("Reading data from input.text");
		ptr = readData(inFile, &noOfRecords, &noOfQuiz);
	} else {
		printf("Please provide information in input.text");
		exit(-1);
	}
	
	printf("\n LastName, TotalScore");
	for(i = 0; i < noOfRecords; i++){
		printf("\n(%s, %d)", (ptr+i) -> lname, (ptr+i) -> total);
	}
	
	printf("\n Student with the highest score");

	int max_total = 0; 
	int max_total_index = 0; 

	for(i = 0; i < noOfRecords; i++){
		if(ptr[i].total > max_total){
			max_total = ptr[i].total;
			max_total_index = i;
		}
	}

	outFile = fopen("output.txt", "w");
	fprintf(outFile, "(%s, %d)", ptr[max_total_index].lname, ptr[max_total_index].total);
	printf("\nOutput.txt generated");

	for(i = 0; i < noOfRecords; i++){
		free(ptr[i].quiz);
	}
	
	free(ptr);
	fclose(inFile);
	fclose(outFile);

	return 0;
}