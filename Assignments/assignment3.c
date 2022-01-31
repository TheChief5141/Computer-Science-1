/*COP 3502C Programming Assignment 3
This program was written by: Logan Kilburn*/

//I don't like binary search. I spent two days trying to figure out how to do it in this program and I never could :(


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct coordinate{
    int x;
    int y;
    double totalDistance;
}coordinate;

int myX = 0;
int myY = 0;

void mergeSort(coordinate * arr, int l, int r, int threshold);
void merge(coordinate * arr, int l, int m, int r);
void insertion_sort(coordinate * arr, int size);
void readData(FILE* fPtr, coordinate *arr, int numOfInfected, int pointsToSearch, int myX, int myY);
int compareTo(coordinate* ptrPt1, coordinate* ptrPt2);
double findDistance(int x, int y, int myX, int myY);
int power(int base, int exponent);
void sort(coordinate *arr, int begArray, int endArray, int threshold);
void printArray(coordinate *arr, int size);
void findPoints(coordinate *arr, FILE* outFile, int begArray, int startingPoint, int endArray);
int binarySearch(coordinate *arr, int l, int r, int x, int y, double distance);

void merge(coordinate *arr, int l, int m, int r){
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;
    int compValue;

    ///create temp arrays
    coordinate *Left = (coordinate*)malloc(n1*sizeof(int));
    coordinate *Right = (coordinate*)malloc(n2*sizeof(int));

    ///copy data to temp arrays L[] and R[]
    for(i = 0; i<n1; i++){
        Left[i].totalDistance = arr[1+i].totalDistance;
    }
    for(j = 0; j < n2; j++){
        Right[j].totalDistance = arr[m+1+j].totalDistance;
    }

    ///Merge the temp arrays back int arr[]
    i = 0;//Intital Index of first subarray
    j = 0;//Intital Index of second array
    k = 1;//Initial Index of merged subarray

    while(i < n1 && j < n2){
        if(Left[i].totalDistance < Right[j].totalDistance){
            arr[k].y = Left[i].y;
            arr[k].x = Left[i].x;
            arr[k].totalDistance = Left[i].totalDistance;
            i++;
        }else if(Left[i].totalDistance == Right[j].totalDistance){
            compValue = compareTo(Left + i, Right + j);
            switch(compValue){
                case 1:
                    arr[k].x = Right[j].x;
                    arr[k].y = Right[j].y;
                    arr[k].totalDistance = Right[j].totalDistance;
                    i++;
                    break;
                case -1:
                    arr[k].x = Left[i].x;
                    arr[k].y = Left[i].y;
                    arr[k].totalDistance = Left[i].totalDistance;
                    j++;
                    break;
                case 0:
                    arr[k].x = Left[i].x;
                    arr[k].y = Left[i].y;
                    arr[k].totalDistance = Left[i].totalDistance;
                    i++;
                    k++;
                    arr[k].x = Right[j].x;
                    arr[k].y = Right[j].y;
                    arr[k].totalDistance = Right[j].totalDistance;
                    j++;
                    break;
            }

        }else{
            arr[k].x = Right[j].x;
            arr[k].y = Right[j].y;
            arr[k].totalDistance = Right[j].totalDistance;
            j++;
        }
        k++;
    }

    ///Copy the remaining elements of L[], if there are any
    while(i < n1){
        arr[k].totalDistance = Left[i].totalDistance;
        i++;
        k++;
    }
    while(j < n2){
        arr[k].totalDistance = Right[j].totalDistance;
        j++;
        k++;
    }

    ///free the data
    free(Left);
    free(Right);
}

void mergeSort(coordinate * arr, int l, int r, int threshold){   
    if(threshold < 30){
        insertion_sort(arr, r);
    } 
    if (l < r){       
        // get the mid point        
        int m = (l+r)/2;        
        // Sort first and second halves        
        mergeSort(arr, l, m, threshold);        
        mergeSort(arr, m+1, r, threshold);       
        //printf("Testing l=%d r=%d m=%d\n", l, r, m);        
        merge(arr, l, m, r);    
    }
}

void insertion_sort(coordinate *arr, int size){
    int i, j, hand, handX, handY;
    for(i = 1; i < size; i++){
        hand = arr[i].totalDistance;
        handX = arr[i].x;
        handY = arr[i].y;
        for(j = (i-1); j >= 0; j--){
            if(arr[j].totalDistance > hand){
                arr[j+1].totalDistance = arr[j].totalDistance;
                arr[j+1].x = arr[j].x;
                arr[j+1].y = arr[j].y;
            }else{
                break;
            }
        }
        arr[j+1].totalDistance = hand;
        arr[j+1].x = handX;
        arr[j+1].y = handY;
    }
}

void readData(FILE* fPtr, coordinate *arr, int numOfInfected, int pointsToSearch, int myX, int myY){
    
    int i;
    for(i = 0; i < numOfInfected; i++){
        fscanf(fPtr, "%d %d", &arr[i].x, &arr[i].y);
        arr[i].totalDistance = findDistance(arr[i].x, arr[i].y, myX, myY);
    }
    for(i = numOfInfected; i < (pointsToSearch + numOfInfected); i++){
        fscanf(fPtr, "%d %d", &arr[i].x, &arr[i].y);
        arr[i].totalDistance = findDistance(arr[i].x, arr[i].y, myX, myY);
    }

}

int compareTo(coordinate* ptrPt1, coordinate* ptrPt2){
    if(ptrPt1->totalDistance < ptrPt2->totalDistance){
        return -1;
    }else if(ptrPt1->totalDistance > ptrPt2->totalDistance){
        return 1;
    }else if((ptrPt1->x == ptrPt2->x) && (ptrPt1->y == ptrPt2->y)){
        return 0;
    }
    if(ptrPt1->totalDistance == ptrPt2->totalDistance){
        if(ptrPt1->x < ptrPt2->x){
            return -1;
        }
        if(ptrPt1->x > ptrPt2->x){
            return 1;
        }
        if(ptrPt1->x == ptrPt2->x){
             if(ptrPt1->y < ptrPt2->y){
                return -1;
            }
            if(ptrPt1->y > ptrPt2->y){
                return 1;
            }
        }
    }
}

double findDistance(int x, int y, int myX, int myY){
    double totalDistance;
    totalDistance = pow(pow(x - myX, 2) + pow(y - myY, 2), 0.5);
    return totalDistance;
}

void sort(coordinate * arr, int begArray, int endArray, int threshold){
    //find what sorting method we need to use
    if(threshold < 30){
        insertion_sort(arr, endArray);
    }else{
        mergeSort(arr, begArray, endArray, threshold);
    }
}

void printArray(coordinate *arr, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("(%d, %d) coordinate for infected %d", arr[i].x, arr[i].y, i+1);
        printf("\n");
    }
}

void findPoints(coordinate *arr, FILE* outFile, int begArray, int startingPoint, int endArray){
    
    int i;
    int resultSearch = 0;

    //binary sort for points

    for(i = startingPoint; i < endArray; i++){
        printf("Running Binary Search\n");
        resultSearch = binarySearch(arr, 0, startingPoint, arr[i].x, arr[i].y, arr[i].totalDistance);
        if(resultSearch >= 0){
            printf("%d %d at Rank %d\n", arr[resultSearch].x, arr[resultSearch].y, resultSearch+1);
            fprintf(outFile, "%d %d at Rank %d\n", arr[resultSearch].x, arr[resultSearch].y, resultSearch+1);
        }else{
            printf("%d %d not found\n", arr[i].x, arr[i].y);
            fprintf(outFile, "%d %d not found\n", arr[i].x, arr[i].y);
        }
    }
}

int binarySearch(coordinate *arr, int l, int r, int x, int y, double distance){ 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
        printf("Checking if the mid is what we are looking for\n");
        if (arr[m].x == x){
            if(arr[m].y == y){
               return m;  
            }
        } 
        printf("Mid is not the right one, so where is it?\n");
        if (arr[m].x < x && arr[m].y < y){
            printf("Left?\n");
            l = m + 1;
        } 
        else if(arr[m].x < x && arr[m].y < y){
            printf("Right?\n");
            r = m - 1; 
        }
    }  
    return -1; 
}  

//main function

int main(){
    int myX, myY;
    int numOfInfected;
    int pointsToSearch;
    int mergeOrInsert;
    int resultFind;
    FILE* readInFile;
    FILE* outFile;
    coordinate * infectedArray;
    printf("Welcome to the Infected Program! Here we will find all the people infected with Covid-19 closest to you!\n");
    
    readInFile = fopen("Assignment3input.txt", "r");
    
    printf("Reading in the File\n");
    fscanf(readInFile, "%d %d %d %d %d", &myX, &myY, &numOfInfected, &pointsToSearch, &mergeOrInsert);
    printf("Creating the array\n");
    infectedArray = (coordinate*)malloc((numOfInfected*pointsToSearch)*sizeof(coordinate));
    readData(readInFile, infectedArray, numOfInfected, pointsToSearch, myX, myY);
    printf("Sorting the array, from closest distance to furthest\n");
    printf("Array before sorting\n");
    printArray(infectedArray, numOfInfected);
    sort(infectedArray, 0, numOfInfected, mergeOrInsert);
    printf("Array after sorting\n");
    printArray(infectedArray, numOfInfected);
    printf("Now we will find the points that we will be wanting to move to\n");
    fclose(readInFile);
    outFile = fopen("out.txt", "w");
    findPoints(infectedArray, outFile, 0, numOfInfected, numOfInfected + pointsToSearch);



    

    
    free(infectedArray);
}