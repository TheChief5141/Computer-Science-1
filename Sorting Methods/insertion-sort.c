#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int A[], int n);

void insertion_sort(int A[], int n){
    int i, j, hand;
    for(i = 1; i < n; i++){
        hand = A[i];
        for(j = (i-1); j >= 0; j--){
            if(A[j] > hand){
                A[j+1] = A[j];
            }else{
                break;
            }
        }
        A[j+1] = hand;
        for(int k = 0; k < 8; k++){
            printf("%d ", A[k]);
            
        }
        printf("\n");
    }
}

int main(){
    int array[8] = {13,6,9,44,18,22,3,11};

    insertion_sort(array, 8);
    for(int i = 0; i < 8; i++){
        printf("\n%d", array[i]);
    }

    return 0;

}