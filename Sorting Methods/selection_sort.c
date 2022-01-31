#include <stdio.h>
#include <stdlib.h>

void selection_sort(int arr[], int size);
void swap(int *exp, int *yp);
void printArray(int arr[], int size);

void printArray(int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d\n", arr[i]);
    }
    printf("\n");
}

void swap(int *exp, int *yp){
    int temp;
    temp = *exp;
    *exp = *yp;
    *yp = temp;
}


void selection_sort(int arr[], int size){
    int i, j;
    int min_index;
    for(i = 0; i < size-1; i++){
        min_index = i;
        for(j = i+1; j < size; j++){
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        swap(&arr[i], &arr[min_index]);
    }

}


int main(){
    int test[100], testcpy[100];
    int num_of_nums, k;
    printf("How many numbers to sort?\n");
    scanf("%d", &num_of_nums);
    for(k = 0; k < num_of_nums; k++){
        printf("Enter number: ");
        scanf("%d", &test[k]);
        testcpy[k] = test[k];
    }
    printf("\nArray before sorting: \n");
    printArray(test, num_of_nums);
    printf("\nArray after sorting: \n");
    selection_sort(testcpy, num_of_nums);
    printArray(testcpy, num_of_nums);

}