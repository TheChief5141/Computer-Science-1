#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXVAL 100000

void selection_sort(int arr[], int size);
void bubble_sort(int arr[], int size);
void merge_sort(int arr[], int l, int m, int r);
void quick_sort(int arr[], int low, int high);
void insertion_sort(int arr[], int size);
long timediff(clock_t t1, clock_t t2);
void swap(int *exp, int *yp);

void insertion_sort(int arr[], int size){
    int i, j, hand;
    for(i = 1; i < size; i++){
        hand = arr[i];
        for(j = (i-1); j >= 0; j--){
            if(arr[j] > hand){
                arr[j+1] = arr[j];
            }else{
                break;
            }
        }
        arr[j+1] = hand;

    }
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

void bubble_sort(int arr[], int size){
    int i, j;
    for(i = 0; i < size-1; i++){
        for(j = 0; j < size - i; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int *L = (int*) malloc(n1*sizeof(int));
    int *R = (int*) malloc(n2*sizeof(int));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
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

       // printf("Testing l=%d r=%d m=%d\n", l, r, m);

        merge(arr, l, m, r);
    }
}


int partition(int arr[], int left, int right)
{
  int i = left+ rand()%(right-left+1);  // random number in the range left- right::: pivot
  
  //we move pivot to the beginning of our array:
  
  swap(&arr[i],&arr[left]);
  int pivot = left;
  //left is one index after pivot:
  
  left++;

 // how long should i update the right nd left and keep walking?
 
 while(left<=right)
 
 {
 
   //left will work:
   while(left <= right && arr[left]<= arr[pivot]) 
   
   
      left++; 
      
      //after left stops , we go to right
   while(left <= right && arr[right]> arr[ pivot])  
        right --;  
        
   //now we must swap right and left. however it is not always the case.
   //if the loop breaks for the reason left>right:
   //we need to swap right with the pivot
   
   if(left< right)
     swap(&arr[left], &arr[right]);
    // end of while and we do the process until they cross each other      
 
 }
 swap(&arr[right], &arr[pivot]);
 
 return right;
}

void quicksort(int arr[], int low, int high)

{
  if (low<high)
  {
    int k= partition(arr, low,high);
    quicksort(arr, low, k-1);
    quicksort(arr,k+1, high);
  
  }
}

void swap(int *exp, int *yp){
    int temp;
    temp = *exp;
    *exp = *yp;
    *yp = temp;
}

long timediff(clock_t t1, clock_t t2){
    long elapsed;
    elapsed = ((double)t2-t1)/CLOCKS_PER_SEC * 1000;

    return elapsed;
}

void arrayCopy(int from[], int to[], int size){
    int i;
    for(i = 0; i < size; i++){
        to[i] = from[i];
    }
}

void randArray(int arr[], int size, int maxVal){
    int i; 
    for(i = 0; i < size; i++){
        arr[i] = rand()%maxVal+1;
    }
}



int main(){
    int sizes[] = {1000, 10000, 20000, 30000, 40000, 50000, 100000};
    int *originalArray;
    int *sortedArray;
    int i, j;
    clock_t t1, t2;
    long elapsed;

    for(i = 0; i < 7; i++){
        originalArray = (int*)malloc(sizeof(int) * sizes[i]);
        sortedArray = (int*)malloc(sizeof(int) * sizes[i]);
        randArray(originalArray, sizes[i], MAXVAL);
        arrayCopy(originalArray, sortedArray, sizes[i]);

        //bubble sort time calculation
        t1 = clock();
        bubble_sort(sortedArray, sizes[i]);
        t2 = clock();
        elapsed = timediff(t1, t2);

        printf("\n Sorting %d values takes %ld milliseconds for Bubble Sort", sizes[i], elapsed);

        //insertion sort time calculation
        randArray(originalArray, sizes[i], MAXVAL);
        arrayCopy(originalArray, sortedArray, sizes[i]);
        t1 = clock();
        insertion_sort(sortedArray, sizes[i]);
        t2 = clock();
        elapsed = timediff(t1, t2);

        printf("\n Sorting %d values takes %ld milliseconds for Insertion Sort", sizes[i], elapsed);

        //selection sort time calculation
        randArray(originalArray, sizes[i], MAXVAL);
        arrayCopy(originalArray, sortedArray, sizes[i]);
        t1 = clock();
        selection_sort(sortedArray, sizes[i]);
        t2 = clock();
        elapsed = timediff(t1, t2);

        printf("\n Sorting %d values takes %ld milliseconds for Selection Sort", sizes[i], elapsed);

        //Merge Sort time calculation
        randArray(originalArray, sizes[i], MAXVAL);
        arrayCopy(originalArray, sortedArray, sizes[i]);
        t1 = clock();
        mergeSort(sortedArray, 0, sizes[i]-1);
        t2 = clock();
        elapsed = timediff(t1, t2);
        printf("\n Sorting %d values takes %ld milliseconds for Merge Sort", sizes[i], elapsed);
        fflush(stdout);


        //quick sort time calculation
        randArray(originalArray, sizes[i], MAXVAL);
        arrayCopy(originalArray, sortedArray, sizes[i]);
        t1 = clock();
        quicksort(sortedArray, 0, sizes[i]-1);
        t2 = clock();
        elapsed = timediff(t1, t2);
        printf("\n Sorting %d values takes %ld milliseconds for Quick Sort", sizes[i], elapsed);
        fflush(stdout);

        free(originalArray);
        free(sortedArray);

        printf("\n");

    }
    return 0;
}



