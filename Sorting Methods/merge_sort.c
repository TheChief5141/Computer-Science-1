#include <stdio.h>
#include <stdlib.h>

void merge_sort(int arr[], int l, int m, int r);
void printArray(int arr[], int size);

void printArray(int arr[], int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d\n", arr[i]);
    }
    printf("\n");
}

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;

    ///create temp arrays
    int *L = (int*)malloc(n1*sizeof(int));
    int *R = (int*)malloc(n2*sizeof(int));

    ///copy data to temp arrays L[] and R[]
    for(i = 0; i<n1; i++){
        L[i] = arr[1+i];
    }
    for(j = 0; j < n2; j++){
        R[j] = arr[m+1+j];
    }

    ///Merge the temp arrays back int arr[]
    i = 0;//Intital Index of first subarray
    j = 0;//Intital Index of second array
    k = 1;//Initial Index of merged subarray

    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    ///Copy the remaining elements of L[], if there are any
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }

    ///free the data
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // get the mid point
        int m = (l+r)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        printf("Testing l=%d r=%d m=%d\n", l, r, m);
        printArray(arr, l+r);

        merge(arr, l, m, r);
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
    printf("\nArray after Merge Sorting: \n");
    mergeSort(testcpy, 0, num_of_nums);
    printArray(testcpy, num_of_nums);

}