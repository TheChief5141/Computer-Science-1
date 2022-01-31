#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 6

int rear;
int front;


typedef struct Customer{
    int accountnum;
    char name[100];
}customer;

customer cs[MAX];

void enqueue(){
    int nr;
    nr=(rear + 1) % MAX;
    if(nr == front){
        printf("\nReached Maximum Capacity, call later");
    }else{
        printf("\nThank you for your call, please enter your customer number:");
        scanf("%d", &cs[rear].accountnum);
        printf("\n Enter name: ");
        scanf("%s", cs[rear].name);
        rear = nr;
    }
}

void dequeue(){
    if(front == rear){
        printf("\nNo customer to serve");
    }else{
        printf("\nCustomer served %d %s", cs[front].accountnum, cs[front].name);
        front = (front + 1) % MAX;
    }

}

void displayQ(){
    int i;
    printf("\nPrinting the queue");
    if(front == rear){
        printf("\n No one in the queue");
    }else{
        if(rear > front){
            for(i = 0; i < rear; i++){
                printf("%d %s", cs[i].accountnum, cs[i].name);
            }
        }else{
            for(i = front; i < MAX; i++){
                printf("%d %s", cs[i].accountnum, cs[i].name);
            }
            for(i = 0; i < rear; i++){
                printf("%d %s", cs[i].accountnum, cs[i].name);
            }
        }
    }
}



void main(){
    front = 0;
    rear = 0;
    char choice[2] = {'c', 's'};
    int index = 0;

    while(1){
        index = rand() % 2;
        if(choice[index] == 'c'){
            printf("\n Customer is trying to call");
            enqueue();
            displayQ();
        }else if(choice[index] == 's'){
            printf("\nServing a customer");
            dequeue();
            displayQ();
        }
    }
}