#include <stdio.h>
#include <stdlib.h>

void swap(int *exp, int *yp);
void printArray(int arr[], int size);
int partition(int arr[], int left, int right);
void quick_sort(int arr[], int low, int high);

void printArray(int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d\n", arr[i]);
    }
    printf("\n");
}

int partition(int arr[], int left, int right){
    int i = left + rand()%(right-left+1);
    swap(&arr[i], &arr[left]);
    int pivot = left;
    left++;

    while(left <= right){
        while(left <= right && arr[left] <= arr[pivot]){
            left++;
        }
        while(left <= right && arr[right] > arr[pivot]){
            right--;
        }
        if(left < right){
            swap(&arr[right], &arr[left]);
        }
            
    }
    swap(&arr[right], &arr[pivot]);

    return right;
}

void swap(int *exp, int *yp){
    int temp;
    temp = *exp;
    *exp = *yp;
    *yp = temp;
}


void quick_sort(int arr[], int low, int high){
    if(low<high){
        int k = partition(arr, low, high);
        quick_sort(arr, low, high);
        quick_sort(arr, k+1, high);
    }
)

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
    printf("\nArray after Quick Sorting: \n");
    quick_sort(testcpy, 0, num_of_nums);
    printArray(testcpy, num_of_nums);

}